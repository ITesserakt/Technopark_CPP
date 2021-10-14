#include <gtest/gtest.h>

extern "C" {
#include "Travel.h"
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
  EXPECT_STREQ(ptr->departure_airport, dep);
  EXPECT_STREQ(ptr->arrival_airport, arr);
  EXPECT_EQ(ptr->flight_duration, duration);
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

TEST(travel, wrong_travel_comparing) {
  Travel *a = nullptr;
  Travel *b = new_travel("ABC", "Moscow", "Stavropol", 2 * 60, 2000);
  EXPECT_NE(b, nullptr);

  EXPECT_EQ(compare_travels_by_cost(a, b), -2);
  EXPECT_EQ(compare_travels_by_cost(b, a), -3);
  EXPECT_EQ(compare_travels_by(b, b, nullptr), -4);

  destroy_travel(b);
}

TEST(travel, finding_minimum) {
  Travel *a = new_travel("ABC", "A", "B", 10, 1);
  Travel *b = new_travel("ABD", "A", "B", 1, 10);
  Travel *c = new_travel("ABE", "A", "C", 1, 1);
  const Travel *array[] = {a, b, c};

  const Travel *min1 = find_min_by(array, 3, "A", "B", compare_travels_by_cost);
  EXPECT_EQ(min1, a);

  const Travel *min2 =
      find_min_by(array, 3, "A", "B", compare_travels_by_duration);
  EXPECT_EQ(min2, b);

  const Travel *min3 = find_min_by(array, 3, "A", "D", compare_travels_by_cost);
  EXPECT_EQ(min3, nullptr);

  const Travel *min4 = find_min_by(array, 0, "A", "B", compare_travels_by_duration);
  EXPECT_EQ(min4, nullptr);

  destroy_travel(a);
  destroy_travel(b);
  destroy_travel(c);
}
