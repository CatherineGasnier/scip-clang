  #include "gtest/gtest.h"
//^ definition [..] `<file>/widget_test.cc`/
//         ^^^^^^^^^^^^^^^ reference [..] `<file>/gtest/gtest.h`/
  #include "widget.h"
//         ^^^^^^^^^^ reference [..] `<file>/widget.h`/
  
  // A helper outside any test class is not test code.
  static Widget makeWidget() { return Widget(3); }
//       ^^^^^^ reference [..] Widget#
//              ^^^^^^^^^^ definition [..] makeWidget(ede618aa334a7c39).
//                                    ^^^^^^ reference [..] Widget#
//                                    ^^^^^^ reference [..] Widget#Widget(d4f767463ce0a6b3).
  
  TEST(WidgetTest, Size) {
//^^^^ reference (test) [..] testing/
//^^^^ reference (test) [..] testing/
//^^^^ reference (test) [..] testing/
//^^^^ reference (test) [..] testing/
//^^^^ reference (test) [..] testing/Test#
//^^^^ reference (test) [..] testing/TestInfo#
//^^^^ reference (test) [..] testing/TestInfo#
//^^^^ reference (test) [..] testing/internal/
//^^^^ reference (test) [..] WidgetTest_Size_Test#
//^^^^ reference (test) [..] WidgetTest_Size_Test#
//^^^^ definition (test) [..] WidgetTest_Size_Test#
//relation implementation [..] testing/Test#
//^^^^ reference (test) [..] `gtest/gtest.h:52:9`!
//^^^^ definition (test) [..] WidgetTest_Size_Test#test_info_.
//^^^^ definition (test) [..] WidgetTest_Size_Test#test_info_.
//^^^^ reference (test) [..] WidgetTest_Size_Test#TestBody(49f6e7a06ebc5aa8).
//^^^^ definition (test) [..] WidgetTest_Size_Test#TestBody(49f6e7a06ebc5aa8).
//relation implementation+reference [..] testing/Test#TestBody(49f6e7a06ebc5aa8).
//^^^^ reference (test) [..] testing/internal/MakeAndRegisterTestInfo(5fd2bd5a17fffc46).
    Widget widget = makeWidget();
//  ^^^^^^ reference (test) [..] Widget#
//         ^^^^^^ definition (test) local 0
//                  ^^^^^^^^^^ reference (test) [..] makeWidget(ede618aa334a7c39).
    EXPECT_EQ(widget.size(), 3);
//  ^^^^^^^^^ reference (test) local 0
//  ^^^^^^^^^ reference (test) [..] testing/
//  ^^^^^^^^^ reference (test) [..] testing/internal/
//  ^^^^^^^^^ reference (test) [..] `gtest/gtest.h:71:9`!
//  ^^^^^^^^^ reference (test) [..] Widget#size(455f465bc33b4cdf).
//  ^^^^^^^^^ reference (test) [..] testing/internal/CmpHelperEQ(cf9ef193275fa6d8).
    Gadget *gadget = newGadget();
//  ^^^^^^ reference (test) [..] Gadget#
//          ^^^^^^ definition (test) local 1
//                   ^^^^^^^^^ reference (test) [..] newGadget(8da3cf5c4fbb3771).
    (void)gadget;
//        ^^^^^^ reference (test) local 1
  }
  
  class WidgetFixture : public ::testing::Test {
//      ^^^^^^^^^^^^^ definition (test) [..] WidgetFixture#
//      relation implementation [..] testing/Test#
//                               ^^^^^^^ reference (test) [..] testing/
//                                        ^^^^ reference (test) [..] testing/Test#
  public:
    void reset() { widget = Widget(0); }
//       ^^^^^ definition (test) [..] WidgetFixture#reset(49f6e7a06ebc5aa8).
//                 ^^^^^^ reference (test) [..] WidgetFixture#widget.
//                        ^ reference (test) [..] Widget#`operator=`(33d495888126150).
//                          ^^^^^^ reference (test) [..] Widget#
//                          ^^^^^^ reference (test) [..] Widget#Widget(d4f767463ce0a6b3).
  
  protected:
    struct Helper {
//         ^^^^^^ definition (test) [..] WidgetFixture#Helper#
      int offset() const;
//        ^^^^^^ reference (test) [..] WidgetFixture#Helper#offset(455f465bc33b4cdf).
    };
    void SetUp() override { widget = makeWidget(); }
//       ^^^^^ definition (test) [..] WidgetFixture#SetUp(49f6e7a06ebc5aa8).
//       relation implementation+reference [..] testing/Test#SetUp(49f6e7a06ebc5aa8).
//                          ^^^^^^ reference (test) [..] WidgetFixture#widget.
//                                 ^ reference (test) [..] Widget#`operator=`(33d495888126150).
//                                   ^^^^^^^^^^ reference (test) [..] makeWidget(ede618aa334a7c39).
    int doubledSize() const;
//      ^^^^^^^^^^^ reference (test) [..] WidgetFixture#doubledSize(455f465bc33b4cdf).
    Widget widget{0};
//  ^^^^^^ reference (test) [..] Widget#
//         ^^^^^^ definition (test) [..] WidgetFixture#widget.
//               ^ reference (test) [..] Widget#Widget(d4f767463ce0a6b3).
  };
  
  int WidgetFixture::doubledSize() const { return 2 * widget.size(); }
//    ^^^^^^^^^^^^^ reference (test) [..] WidgetFixture#
//                   ^^^^^^^^^^^ definition (test) [..] WidgetFixture#doubledSize(455f465bc33b4cdf).
//                                                    ^^^^^^ reference (test) [..] WidgetFixture#widget.
//                                                           ^^^^ reference (test) [..] Widget#size(455f465bc33b4cdf).
  
  // A member of a class nested in a test class is test code too.
  int WidgetFixture::Helper::offset() const { return 0; }
//    ^^^^^^^^^^^^^ reference (test) [..] WidgetFixture#
//                   ^^^^^^ reference (test) [..] WidgetFixture#Helper#
//                           ^^^^^^ definition (test) [..] WidgetFixture#Helper#offset(455f465bc33b4cdf).
  
  // Not test code, even though it names a member of a test class.
  class WidgetResetter {
//      ^^^^^^^^^^^^^^ definition [..] WidgetResetter#
    friend void WidgetFixture::reset();
//              ^^^^^^^^^^^^^ reference [..] WidgetFixture#
//                             ^^^^^ reference [..] WidgetFixture#reset(49f6e7a06ebc5aa8).
  };
  
  // Derives from a GoogleTest class other than ::testing::Test: not test code.
  class WidgetEnvironment : public ::testing::Environment {
//      ^^^^^^^^^^^^^^^^^ definition [..] WidgetEnvironment#
//      relation implementation [..] testing/Environment#
//                                   ^^^^^^^ reference [..] testing/
//                                            ^^^^^^^^^^^ reference [..] testing/Environment#
  public:
    void SetUp() override {}
//       ^^^^^ definition [..] WidgetEnvironment#SetUp(49f6e7a06ebc5aa8).
//       relation implementation+reference [..] testing/Environment#SetUp(49f6e7a06ebc5aa8).
  };
  
  TEST_F(WidgetFixture, DoubledSize) {
//^^^^^^ reference (test) [..] testing/
//^^^^^^ reference (test) [..] testing/
//^^^^^^ reference (test) [..] testing/
//^^^^^^ reference (test) [..] WidgetFixture#
//^^^^^^ reference (test) [..] testing/TestInfo#
//^^^^^^ reference (test) [..] testing/TestInfo#
//^^^^^^ reference (test) [..] testing/internal/
//^^^^^^ reference (test) [..] `gtest/gtest.h:55:9`!
//^^^^^^ reference (test) [..] WidgetFixture_DoubledSize_Test#
//^^^^^^ reference (test) [..] WidgetFixture_DoubledSize_Test#
//^^^^^^ definition (test) [..] WidgetFixture_DoubledSize_Test#
//relation implementation [..] WidgetFixture#
//relation implementation [..] testing/Test#
//^^^^^^ definition (test) [..] WidgetFixture_DoubledSize_Test#test_info_.
//^^^^^^ definition (test) [..] WidgetFixture_DoubledSize_Test#test_info_.
//^^^^^^ reference (test) [..] WidgetFixture_DoubledSize_Test#TestBody(49f6e7a06ebc5aa8).
//^^^^^^ definition (test) [..] WidgetFixture_DoubledSize_Test#TestBody(49f6e7a06ebc5aa8).
//relation implementation+reference [..] testing/Test#TestBody(49f6e7a06ebc5aa8).
//^^^^^^ reference (test) [..] testing/internal/MakeAndRegisterTestInfo(5fd2bd5a17fffc46).
    EXPECT_EQ(doubledSize(), 6);
//  ^^^^^^^^^ reference (test) [..] testing/
//  ^^^^^^^^^ reference (test) [..] testing/internal/
//  ^^^^^^^^^ reference (test) [..] `gtest/gtest.h:71:9`!
//  ^^^^^^^^^ reference (test) [..] WidgetFixture#doubledSize(455f465bc33b4cdf).
//  ^^^^^^^^^ reference (test) [..] testing/internal/CmpHelperEQ(cf9ef193275fa6d8).
  }
  
  template <typename T> class TypedFixture : public ::testing::Test {
//                   ^ definition (test) local 2
//                            ^^^^^^^^^^^^ definition (test) [..] TypedFixture#
//                            relation implementation [..] testing/Test#
//                                                    ^^^^^^^ reference (test) [..] testing/
//                                                             ^^^^ reference (test) [..] testing/Test#
  protected:
    T value{};
//  ^ reference (test) local 2
//    ^^^^^ definition (test) [..] TypedFixture#value.
  };
  
  TYPED_TEST(TypedFixture, ValueIsZero) {
//^^^^^^^^^^ reference (test) local 3
//^^^^^^^^^^ reference (test) local 3
//^^^^^^^^^^ definition (test) local 3
//^^^^^^^^^^ definition (test) local 4
//^^^^^^^^^^ reference (test) [..] testing/
//^^^^^^^^^^ reference (test) [..] TypedFixture#
//^^^^^^^^^^ reference (test) [..] testing/internal/
//^^^^^^^^^^ reference (test) [..] `gtest/gtest.h:58:9`!
//^^^^^^^^^^ reference (test) [..] TypedFixture_ValueIsZero_Test#
//^^^^^^^^^^ definition (test) [..] TypedFixture_ValueIsZero_Test#
//relation implementation [..] TypedFixture#
//relation implementation [..] testing/Test#
//^^^^^^^^^^ definition (test) [..] TypedFixture_ValueIsZero_Test#TypeParam#
//^^^^^^^^^^ definition (test) [..] gtest_TypedFixture_ValueIsZero_registered_.
//^^^^^^^^^^ reference (test) [..] testing/internal/RegisterTypedTest(b7a7aa4a824b7595).
//^^^^^^^^^^ reference (test) [..] TypedFixture_ValueIsZero_Test#TestBody(49f6e7a06ebc5aa8).
//^^^^^^^^^^ definition (test) [..] TypedFixture_ValueIsZero_Test#TestBody(49f6e7a06ebc5aa8).
    EXPECT_EQ(this->value, 0);
//  ^^^^^^^^^ reference (test) [..] testing/
//  ^^^^^^^^^ reference (test) [..] testing/internal/
//  ^^^^^^^^^ reference (test) [..] TypedFixture#value.
//  ^^^^^^^^^ reference (test) [..] `gtest/gtest.h:71:9`!
//  ^^^^^^^^^ reference (test) [..] testing/internal/CmpHelperEQ(cf9ef193275fa6d8).
  }
