#include "llvm/Support/Casting.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/DeclBase.h"
#include "clang/AST/DeclCXX.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"

#include "indexer/TestCodeDetector.h"

namespace scip_clang {
namespace {

/// Matches the definition of a class deriving, directly or indirectly, from
/// \c ::testing::Test.
///
/// The matcher follows dependent bases such as \c Fixture<T>, which
/// \c TYPED_TEST uses, through their primary template, and stops at classes
/// that are their own base through a primary template, like
/// 'template <int N> struct S : S<N - 1> {};'.
const clang::ast_matchers::DeclarationMatcher &testClassMatcher() {
  static const clang::ast_matchers::DeclarationMatcher matcher =
      clang::ast_matchers::cxxRecordDecl(
          clang::ast_matchers::isDerivedFrom("::testing::Test"));
  return matcher;
}

} // namespace

bool TestCodeDetector::isTestCodeRoot(const clang::Decl &decl) {
  return this->isTestClassDefinition(decl)
         || this->isOutOfLineMemberOfTestClass(decl);
}

bool TestCodeDetector::isTestClassDefinition(const clang::Decl &decl) {
  // For a class template, start at the template itself, so that the
  // template parameter list counts as test code too.
  const clang::Decl *classDecl = &decl;
  if (auto *classTemplateDecl =
          llvm::dyn_cast<clang::ClassTemplateDecl>(&decl)) {
    classDecl = classTemplateDecl->getTemplatedDecl();
  }
  auto *record = llvm::dyn_cast<clang::CXXRecordDecl>(classDecl);
  // Forward declarations don't count: FRIEND_TEST(...) expands to
  // 'friend class SomeTest;' inside the (non-test) class under test.
  return record && record->isThisDeclarationADefinition()
         && this->isTestClass(*record);
}

bool TestCodeDetector::isOutOfLineMemberOfTestClass(const clang::Decl &decl) {
  // The translation unit has no parent, and Decl::isOutOfLine assumes one.
  if (!decl.getDeclContext() || !decl.isOutOfLine()) {
    return false;
  }
  // 'friend void SomeTest::f();' in another class only names the member.
  if (decl.getFriendObjectKind() != clang::Decl::FOK_None) {
    return false;
  }
  for (auto *context = decl.getDeclContext(); context;
       context = context->getParent()) {
    if (auto *record = llvm::dyn_cast<clang::CXXRecordDecl>(context)) {
      if (this->isTestClass(*record)) {
        return true;
      }
    }
  }
  return false;
}

bool TestCodeDetector::isTestClass(const clang::CXXRecordDecl &record) {
  auto *definition = record.getDefinition();
  if (!definition) {
    return false;
  }
  auto it = this->isTestClassCache.find(definition);
  if (it != this->isTestClassCache.end()) {
    return it->second;
  }
  bool isTest = !clang::ast_matchers::match(testClassMatcher(), *definition,
                                            definition->getASTContext())
                     .empty();
  this->isTestClassCache.emplace(definition, isTest);
  return isTest;
}

} // namespace scip_clang
