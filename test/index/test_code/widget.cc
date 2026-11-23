// Code under test. None of it is test code.
#include "widget.h"

struct Gadget {
  int id;
};

Gadget *newGadget() { return new Gadget{1}; }

int Widget::size() const { return size_; }

namespace other {
class Test {};
namespace testing {
class Test {};
} // namespace testing
} // namespace other

// These derive from classes named Test, but not from ::testing::Test.
class NotATest : public other::Test {
  void TestBody() {}
};
class AlsoNotATest : public other::testing::Test {};

// Recursive inheritance through a dependent base.
template <int N> struct Countdown : Countdown<N - 1> {};
template <> struct Countdown<0> {};
