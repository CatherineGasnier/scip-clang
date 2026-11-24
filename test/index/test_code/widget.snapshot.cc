  // Code under test. None of it is test code.
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ definition [..] `<file>/widget.cc`/
  #include "widget.h"
//         ^^^^^^^^^^ reference [..] `<file>/widget.h`/
  
  struct Gadget {
//       ^^^^^^ definition [..] Gadget#
    int id;
//      ^^ definition [..] Gadget#id.
  };
  
  Gadget *newGadget() { return new Gadget{1}; }
//^^^^^^ reference [..] Gadget#
//        ^^^^^^^^^ definition [..] newGadget(8da3cf5c4fbb3771).
//                                 ^^^^^^ reference [..] Gadget#
  
  int Widget::size() const { return size_; }
//    ^^^^^^ reference [..] Widget#
//            ^^^^ definition [..] Widget#size(455f465bc33b4cdf).
//                                  ^^^^^ reference [..] Widget#size_.
  
  namespace other {
//          ^^^^^ definition [..] other/
  class Test {};
//      ^^^^ definition [..] other/Test#
  namespace testing {
//          ^^^^^^^ definition [..] other/testing/
  class Test {};
//      ^^^^ definition [..] other/testing/Test#
  } // namespace testing
  } // namespace other
  
  // These derive from classes named Test, but not from ::testing::Test.
  class NotATest : public other::Test {
//      ^^^^^^^^ definition [..] NotATest#
//      relation implementation [..] other/Test#
//                        ^^^^^ reference [..] other/
//                               ^^^^ reference [..] other/Test#
    void TestBody() {}
//       ^^^^^^^^ definition [..] NotATest#TestBody(49f6e7a06ebc5aa8).
  };
  class AlsoNotATest : public other::testing::Test {};
//      ^^^^^^^^^^^^ definition [..] AlsoNotATest#
//      relation implementation [..] other/testing/Test#
//                            ^^^^^ reference [..] other/
//                                   ^^^^^^^ reference [..] other/testing/
//                                            ^^^^ reference [..] other/testing/Test#
  
  // Recursive inheritance through a dependent base.
  template <int N> struct Countdown : Countdown<N - 1> {};
//              ^ definition local 0
//                        ^^^^^^^^^ definition [..] Countdown#
//                                    ^^^^^^^^^ reference [..] Countdown#
//                                              ^ reference local 0
  template <> struct Countdown<0> {};
//                   ^^^^^^^^^ reference [..] Countdown#
//                   ^^^^^^^^^ definition [..] Countdown#
