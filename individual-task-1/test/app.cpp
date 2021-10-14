#include <gtest/gtest.h>

extern "C" {
#include "Application.h"
#include "utils.h"
}

TEST(app, correct_travel_loading) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s\n%s\n%d %d", "YEF", "New York", "Los Angeles", 1 * 60,
          400);
  rewind(test);

  Travel *travel = load_travel(test, stderr);
  EXPECT_NE(travel, nullptr);
  EXPECT_STREQ(travel->code, "YEF");
  EXPECT_STREQ(travel->departure_airport, "New York");
  EXPECT_STREQ(travel->arrival_airport, "Los Angeles");
  EXPECT_EQ(travel->flight_duration, 60);
  EXPECT_EQ(travel->cost, 400);

  destroy_travel(travel);
  fclose(test);
}

TEST(app, wrong_travel_loading) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s\n%s\n%d %s", "YEF", "New York", "Los Angeles", 1 * 60,
          "o la la");
  rewind(test);

  Travel *travel = load_travel(test, stderr);
  EXPECT_EQ(travel, nullptr);
  fclose(test);
}

TEST(app, wrong_travel_code) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s\n%s\n%d %d", "Meow", "New York", "Los Angeles", 1 * 60,
          400);
  rewind(test);

  Travel *travel = load_travel(test, stderr);
  EXPECT_EQ(travel, nullptr);
  fclose(test);
}

TEST(app, travels_loading) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s %s\n%s\n%d %d\n", "YEF", "New York", "Los Angeles", 1 * 60,
          400);
  fprintf(test, "%s\n%s\n%s\n%d %d", "IHB", "London", "Moscow", 3 * 60, 6000);
  rewind(test);

  size_t length = 0;
  const Travel **travels = load_travels(test, stderr, &length);
  EXPECT_NE(travels, nullptr);
  EXPECT_EQ(length, 2);
  for (int i = 0; i < length; i++)
    EXPECT_NE(travels[i], nullptr);

  EXPECT_STREQ(travels[0]->code, "YEF");
  EXPECT_STREQ(travels[0]->departure_airport, "New York");
  EXPECT_STREQ(travels[0]->arrival_airport, "Los Angeles");
  EXPECT_EQ(travels[0]->flight_duration, 60);
  EXPECT_EQ(travels[0]->cost, 400);

  EXPECT_STREQ(travels[1]->code, "IHB");
  EXPECT_STREQ(travels[1]->departure_airport, "London");
  EXPECT_STREQ(travels[1]->arrival_airport, "Moscow");
  EXPECT_EQ(travels[1]->flight_duration, 180);
  EXPECT_EQ(travels[1]->cost, 6000);

  for (int i = 0; i < length; i++)
    destroy_travel(const_cast<Travel *>(travels[i]));
  free(travels);
  fclose(test);
}

TEST(app, giant_array) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  for (long i = 0; i < 100000; i++)
    fprintf(test, "%s\n%s\n%s\n%d %d\n", "YEF", "New York", "Los Angeles",
            1 * 60, 1);
  rewind(test);

  size_t length = 0;
  const Travel **travels = load_travels(test, stderr, &length);
  EXPECT_NE(travels, nullptr);
  EXPECT_EQ(length, 100000);

  for (int i = 0; i < length; i++)
    destroy_travel(const_cast<Travel *>(travels[i]));
  free(travels);
  fclose(test);
}