// Code under test. None of it is test code.
#pragma once

#include "gtest/gtest_prod.h"

struct Gadget;
Gadget *newGadget();

class Widget {
public:
  explicit Widget(int size) : size_(size) {}
  int size() const;

private:
  // Names a test class, but is not test code.
  FRIEND_TEST(WidgetTest, Size);
  int size_;
};
