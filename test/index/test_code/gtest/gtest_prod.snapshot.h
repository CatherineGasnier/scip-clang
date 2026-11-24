  // A minimal stand-in for GoogleTest's gtest/gtest_prod.h.
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ definition [..] `<file>/gtest/gtest_prod.h`/
  #pragma once
  
  #define FRIEND_TEST(test_suite_name, test_name) \
//        ^^^^^^^^^^^ definition [..] `gtest/gtest_prod.h:4:9`!
    friend class test_suite_name##_##test_name##_Test
