#include "gtest/gtest.h"
#include "widget.h"

// A helper outside any test class is not test code.
static Widget makeWidget() { return Widget(3); }

TEST(WidgetTest, Size) {
  Widget widget = makeWidget();
  EXPECT_EQ(widget.size(), 3);
  Gadget *gadget = newGadget();
  (void)gadget;
}

class WidgetFixture : public ::testing::Test {
public:
  void reset() { widget = Widget(0); }

protected:
  struct Helper {
    int offset() const;
  };
  void SetUp() override { widget = makeWidget(); }
  int doubledSize() const;
  Widget widget{0};
};

int WidgetFixture::doubledSize() const { return 2 * widget.size(); }

// A member of a class nested in a test class is test code too.
int WidgetFixture::Helper::offset() const { return 0; }

// Not test code, even though it names a member of a test class.
class WidgetResetter {
  friend void WidgetFixture::reset();
};

// Derives from a GoogleTest class other than ::testing::Test: not test code.
class WidgetEnvironment : public ::testing::Environment {
public:
  void SetUp() override {}
};

TEST_F(WidgetFixture, DoubledSize) {
  EXPECT_EQ(doubledSize(), 6);
}

template <typename T> class TypedFixture : public ::testing::Test {
protected:
  T value{};
};

TYPED_TEST(TypedFixture, ValueIsZero) {
  EXPECT_EQ(this->value, 0);
}
