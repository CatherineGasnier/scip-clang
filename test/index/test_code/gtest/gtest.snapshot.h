  // A minimal stand-in for GoogleTest's gtest/gtest.h. The macros expand
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ definition [..] `<file>/gtest/gtest.h`/
  // to code with the same shape as the code that GoogleTest's macros
  // expand to, minus the parts irrelevant to indexing.
  #pragma once
  
  #include "gtest/gtest_prod.h"
//         ^^^^^^^^^^^^^^^^^^^^ reference [..] `<file>/gtest/gtest_prod.h`/
  
  namespace testing {
//          ^^^^^^^ definition [..] testing/
  
  class Test {
//      ^^^^ definition [..] testing/Test#
  public:
    virtual ~Test() = default;
//          ^ definition [..] testing/Test#`~Test`(ced63f7c635d850d).
//           ^^^^ reference [..] testing/Test#
    virtual void SetUp() {}
//               ^^^^^ definition [..] testing/Test#SetUp(49f6e7a06ebc5aa8).
    virtual void TearDown() {}
//               ^^^^^^^^ definition [..] testing/Test#TearDown(49f6e7a06ebc5aa8).
  
  private:
    virtual void TestBody() = 0;
//               ^^^^^^^^ definition [..] testing/Test#TestBody(49f6e7a06ebc5aa8).
  };
  
  class Environment {
//      ^^^^^^^^^^^ definition [..] testing/Environment#
  public:
    virtual ~Environment() = default;
//          ^ definition [..] testing/Environment#`~Environment`(ced63f7c635d850d).
//           ^^^^^^^^^^^ reference [..] testing/Environment#
    virtual void SetUp() {}
//               ^^^^^ definition [..] testing/Environment#SetUp(49f6e7a06ebc5aa8).
  };
  
  class TestInfo {};
//      ^^^^^^^^ definition [..] testing/TestInfo#
  
  namespace internal {
//          ^^^^^^^^ definition [..] testing/internal/
  TestInfo *MakeAndRegisterTestInfo(const char *suite, const char *name);
//^^^^^^^^ reference [..] testing/TestInfo#
//          ^^^^^^^^^^^^^^^^^^^^^^^ reference [..] testing/internal/MakeAndRegisterTestInfo(5fd2bd5a17fffc46).
//                                              ^^^^^ definition local 0
//                                                                 ^^^^ definition local 1
  bool RegisterTypedTest(const char *suite, const char *name);
//     ^^^^^^^^^^^^^^^^^ reference [..] testing/internal/RegisterTypedTest(b7a7aa4a824b7595).
//                                   ^^^^^ definition local 2
//                                                      ^^^^ definition local 3
  bool CmpHelperEQ(int lhs, int rhs);
//     ^^^^^^^^^^^ reference [..] testing/internal/CmpHelperEQ(cf9ef193275fa6d8).
//                     ^^^ definition local 4
//                              ^^^ definition local 5
  } // namespace internal
  
  } // namespace testing
  
  #define GTEST_TEST_CLASS_NAME_(test_suite_name, test_name) \
//        ^^^^^^^^^^^^^^^^^^^^^^ definition [..] `gtest/gtest.h:36:9`!
    test_suite_name##_##test_name##_Test
  
  #define GTEST_TEST_(test_suite_name, test_name, parent_class)                 \
//        ^^^^^^^^^^^ definition [..] `gtest/gtest.h:39:9`!
    class GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)                    \
//        ^^^^^^^^^^^^^^^^^^^^^^ reference [..] `gtest/gtest.h:36:9`!
        : public parent_class {                                                 \
    private:                                                                    \
      void TestBody() override;                                                 \
      static ::testing::TestInfo *const test_info_;                             \
    };                                                                          \
    ::testing::TestInfo *const GTEST_TEST_CLASS_NAME_(test_suite_name,          \
//                             ^^^^^^^^^^^^^^^^^^^^^^ reference [..] `gtest/gtest.h:36:9`!
                                                      test_name)::test_info_ =  \
        ::testing::internal::MakeAndRegisterTestInfo(#test_suite_name,          \
                                                     #test_name);               \
    void GTEST_TEST_CLASS_NAME_(test_suite_name, test_name)::TestBody()
//       ^^^^^^^^^^^^^^^^^^^^^^ reference [..] `gtest/gtest.h:36:9`!
  
  #define TEST(test_suite_name, test_name) \
//        ^^^^ definition [..] `gtest/gtest.h:52:9`!
    GTEST_TEST_(test_suite_name, test_name, ::testing::Test)
//  ^^^^^^^^^^^ reference [..] `gtest/gtest.h:39:9`!
  
  #define TEST_F(test_fixture, test_name) \
//        ^^^^^^ definition [..] `gtest/gtest.h:55:9`!
    GTEST_TEST_(test_fixture, test_name, test_fixture)
//  ^^^^^^^^^^^ reference [..] `gtest/gtest.h:39:9`!
  
  #define TYPED_TEST(CaseName, TestName)                                       \
//        ^^^^^^^^^^ definition [..] `gtest/gtest.h:58:9`!
    template <typename gtest_TypeParam_>                                       \
    class GTEST_TEST_CLASS_NAME_(CaseName, TestName)                           \
//        ^^^^^^^^^^^^^^^^^^^^^^ reference [..] `gtest/gtest.h:36:9`!
        : public CaseName<gtest_TypeParam_> {                                  \
    private:                                                                   \
      typedef gtest_TypeParam_ TypeParam;                                      \
      void TestBody() override;                                                \
    };                                                                         \
    static bool gtest_##CaseName##_##TestName##_registered_ =                  \
        ::testing::internal::RegisterTypedTest(#CaseName, #TestName);          \
    template <typename gtest_TypeParam_>                                       \
    void GTEST_TEST_CLASS_NAME_(CaseName, TestName)<gtest_TypeParam_>::TestBody()
//       ^^^^^^^^^^^^^^^^^^^^^^ reference [..] `gtest/gtest.h:36:9`!
  
  #define EXPECT_EQ(val1, val2) ::testing::internal::CmpHelperEQ(val1, val2)
//        ^^^^^^^^^ definition [..] `gtest/gtest.h:71:9`!
