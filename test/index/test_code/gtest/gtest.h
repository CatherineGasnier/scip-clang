// A minimal stand-in for GoogleTest's gtest/gtest.h. The macros expand
// to code with the same shape as the code that GoogleTest's macros
// expand to, minus the parts irrelevant to indexing.
#pragma once

#include "gtest/gtest_prod.h"

namespace testing {

class Test {
public:
  virtual ~Test() = default;
  virtual void SetUp() {}
  virtual void TearDown() {}

private:
  virtual void TestBody() = 0;
};

class Environment {
public:
  virtual ~Environment() = default;
  virtual void SetUp() {}
};

class TestInfo {};

namespace internal {
TestInfo *MakeAndRegisterTestInfo(const char *suite, const char *name);
bool RegisterTypedTest(const char *suite, const char *name);
bool CmpHelperEQ(int lhs, int rhs);
} // namespace internal

} // namespace testing

#define GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) \
  test_suite_name##_##test_name##_Test

#define GTEST_TEST_(test_suite_name, test_name, parent_class)                 \
  class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                    \
      : public parent_class {                                                 \
  private:                                                                    \
    void TestBody() override;                                                 \
    static ::testing::TestInfo *const test_info_;                             \
  };                                                                          \
  ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,          \
                                                    test_name)::test_info_ =  \
      ::testing::internal::MakeAndRegisterTestInfo(#test_suite_name,          \
                                                   #test_name);               \
  void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody()

#define TEST(test_suite_name, test_name) \
  GTEST_TEST_(test_suite_name, test_name, ::testing::Test)

#define TEST_F(test_fixture, test_name) \
  GTEST_TEST_(test_fixture, test_name, test_fixture)

#define TYPED_TEST(CaseName, TestName)                                       \
  template <typename gtest_TypeParam_>                                       \
  class GTEST_TEST_CLASS_NAME_(CaseName, TestName)                           \
      : public CaseName<gtest_TypeParam_> {                                  \
  private:                                                                   \
    typedef gtest_TypeParam_ TypeParam;                                      \
    void TestBody() override;                                                \
  };                                                                         \
  static bool gtest_##CaseName##_##TestName##_registered_ =                  \
      ::testing::internal::RegisterTypedTest(#CaseName, #TestName);          \
  template <typename gtest_TypeParam_>                                       \
  void GTEST_TEST_CLASS_NAME_(CaseName, TestName)<gtest_TypeParam_>::TestBody()

#define EXPECT_EQ(val1, val2) ::testing::internal::CmpHelperEQ(val1, val2)
