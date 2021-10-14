#include <gtest/gtest.h>

extern "C" {
#include "utils.h"
}

TEST(utils, multiple_free) {
  char *p1 = static_cast<char *>(malloc(sizeof(char)));
  char *p2 = static_cast<char *>(malloc(sizeof(char)));

  free_many(2, &p1, &p2);
  EXPECT_EQ(p1, nullptr);
  EXPECT_EQ(p2, nullptr);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
