#include <gtest/gtest.h>

extern "C" {
#include "Application.h"
#include "Travel.h"
#include "IO.h"
#include "utils.h"
}

TEST(travel, travel_creating) {
  char code[] = "ABC";
  const char *dep = "Moscow";
  const char *arr = "Stavropol";
  unsigned int duration = 2 * 60;
  unsigned int cost = 2000 / 75;
  Travel *ptr = new_travel(code, dep, arr, duration, cost);

  EXPECT_NE(ptr, nullptr);
  EXPECT_STREQ(ptr->code, code);
  EXPECT_STREQ(ptr->departureAirport, dep);
  EXPECT_STREQ(ptr->arrivalAirport, arr);
  EXPECT_EQ(ptr->flightDuration, duration);
  EXPECT_EQ(ptr->cost, cost);

  destroy_travel(ptr);
}

TEST(travel, travel_comparing) {
  Travel *a = new_travel("ABC", "Moscow", "Stavropol", 2 * 60, 2000);
  EXPECT_NE(a, nullptr);
  Travel *b = new_travel("ABC", "Moscow", "Stavropol", 2.4 * 60, 1500);
  if (b == nullptr) {
    destroy_travel(a);
    EXPECT_NE(b, nullptr);
  }

  EXPECT_EQ(compare_travels_by_cost(a, b), 1);
  EXPECT_EQ(compare_travels_by_duration(a, b), -1);
  EXPECT_EQ(compare_travels_by_cost(a, a), 0);
  EXPECT_EQ(compare_travels_by_duration(a, a), 0);

  destroy_travel(a);
  destroy_travel(b);
}

TEST(travel, wrong_travel) {
  Travel *a = nullptr;
  Travel *b = new_travel("ABC", "Moscow", "Stavropol", 2 * 60, 2000);
  EXPECT_NE(b, nullptr);

  EXPECT_EQ(compare_travels_by_cost(a, b), -2);
  EXPECT_EQ(compare_travels_by_cost(b, a), -3);
  EXPECT_EQ(compare_travels_by(b, b, nullptr), -4);

  destroy_travel(b);
}

TEST(reader, get_line) {
  FILE *test = fopen("test.txt", "w");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s", "Hello, world!", "That's a test!");
  fprintf(test, "\n%s", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  fclose(test);

  test = fopen("test.txt", "r");
  ASSERT_NE(test, nullptr);
  char *a = read_line(test);
  char *b = read_line(test);
  char *c = read_line(test);

  EXPECT_STREQ(a, "Hello, world!");
  EXPECT_STREQ(b, "That's a test!");
  EXPECT_STREQ(c, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

  free_many(3, &a, &b, &c);
}

TEST(app, no_throw) {
  ASSERT_NO_THROW({
                    char **argv = {nullptr};
                    run(0, argv);
                  });
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