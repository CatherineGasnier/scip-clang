#ifndef SCIP_CLANG_TEST_CODE_DETECTOR_H
#define SCIP_CLANG_TEST_CODE_DETECTOR_H

#include "absl/container/flat_hash_map.h"

namespace clang {
class CXXRecordDecl;
class Decl;
} // namespace clang

namespace scip_clang {

// NOTE(def: test-code)
// Occurrences located in test code get scip::SymbolRole::Test, in addition
// to their other roles.
//
// Test code is the code that GoogleTest itself treats as a test: the code
// of a test class, i.e. a class deriving, directly or indirectly, from
// ::testing::Test. The TEST, TEST_F, TEST_P and TYPED_TEST macros all expand
// to such a class, whose TestBody() method, defined outside the class, holds
// the test body. Fixtures derive from ::testing::Test too.
//
// An occurrence is test code if it starts inside the source range of:
// 1. the definition of a test class, or
// 2. a definition written outside the body of the test class it belongs to,
//    possibly through nested classes, such as TestBody().
// The rest of a test class's code is inside one of these ranges. Occurrences
// inside macro expansions are located at the macro invocation, so the ranges
// are expansion ranges too.
//
// Code outside such classes, such as a helper function in a *_test.cc file,
// is not test code by this definition.

/// Decides which declarations are test code by themselves, without looking
/// at the declarations enclosing them. See NOTE(ref: test-code).
class TestCodeDetector final {
  /// Caches results of \c isTestClass, keyed by class definition.
  absl::flat_hash_map<const clang::CXXRecordDecl *, bool> isTestClassCache;

public:
  TestCodeDetector() = default;

  /// Returns true for the declarations 1. and 2. of NOTE(ref: test-code).
  ///
  /// Everything within the source range of such a declaration is test code,
  /// including nested declarations, for which this method may return false.
  bool isTestCodeRoot(const clang::Decl &);

private:
  bool isTestClassDefinition(const clang::Decl &);

  bool isOutOfLineMemberOfTestClass(const clang::Decl &);

  /// Returns true if \p record derives, directly or indirectly, from
  /// \c ::testing::Test.
  bool isTestClass(const clang::CXXRecordDecl &record);
};

} // namespace scip_clang

#endif // SCIP_CLANG_TEST_CODE_DETECTOR_H
