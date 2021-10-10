#include <gtest/gtest.h>

extern "C" {
// place here c headers
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}