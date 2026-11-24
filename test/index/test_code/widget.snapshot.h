  // Code under test. None of it is test code.
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ definition [..] `<file>/widget.h`/
  #pragma once
  
  #include "gtest/gtest_prod.h"
//         ^^^^^^^^^^^^^^^^^^^^ reference [..] `<file>/gtest/gtest_prod.h`/
  
  struct Gadget;
//       ^^^^^^ reference [..] Gadget#
//       ^^^^^^ reference [..] Gadget#
  Gadget *newGadget();
//^^^^^^ reference [..] Gadget#
//^^^^^^ reference [..] Gadget#
//        ^^^^^^^^^ reference [..] newGadget(8da3cf5c4fbb3771).
//        ^^^^^^^^^ reference [..] newGadget(8da3cf5c4fbb3771).
  
  class Widget {
//      ^^^^^^ definition [..] Widget#
  public:
    explicit Widget(int size) : size_(size) {}
//           ^^^^^^ definition [..] Widget#Widget(d4f767463ce0a6b3).
//                      ^^^^ definition local 0
//                              ^^^^^ reference [..] Widget#size_.
//                                    ^^^^ reference local 0
    int size() const;
//      ^^^^ reference [..] Widget#size(455f465bc33b4cdf).
//      ^^^^ reference [..] Widget#size(455f465bc33b4cdf).
  
  private:
    // Names a test class, but is not test code.
    FRIEND_TEST(WidgetTest, Size);
//  ^^^^^^^^^^^ reference [..] WidgetTest_Size_Test#
//  ^^^^^^^^^^^ reference [..] WidgetTest_Size_Test#
//  ^^^^^^^^^^^ reference [..] WidgetTest_Size_Test#
//  ^^^^^^^^^^^ reference [..] WidgetTest_Size_Test#
//  ^^^^^^^^^^^ reference [..] `gtest/gtest_prod.h:4:9`!
    int size_;
//      ^^^^^ definition [..] Widget#size_.
  };
