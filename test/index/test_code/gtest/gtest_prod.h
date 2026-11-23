// A minimal stand-in for GoogleTest's gtest/gtest_prod.h.
#pragma once

#define FRIEND_TEST(test_suite_name, test_name) \
  friend class test_suite_name##_##test_name##_Test
