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
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s", "Hello, world!", "That's a test!");
  fprintf(test,
          "\n%s\n\n",
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  rewind(test);

  char *a = read_line(test);
  char *b = read_line(test);
  char *c = read_line(test);
  char *d = read_line(test);
  fclose(test);

  EXPECT_STREQ(a, "Hello, world!");
  EXPECT_STREQ(b, "That's a test!");
  EXPECT_STREQ(c, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  EXPECT_EQ(d, nullptr);

  free_many(3, &a, &b, &c, &d);
}

TEST(reader, get_word) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s", "Hello, world!", "That's a test!");
  fprintf(test,
          "\n%s\n\n",
          "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  rewind(test);

  char *a = read_word(test);
  char *b = read_word(test);
  char *c = read_word(test);
  char *d = read_word(test);
  char *e = read_word(test);
  char *f = read_word(test);
  char *g = read_word(test);
  fclose(test);

  EXPECT_STREQ(a, "Hello,");
  EXPECT_STREQ(b, "world!");
  EXPECT_STREQ(c, "That's");
  EXPECT_STREQ(d, "a");
  EXPECT_STREQ(e, "test!");
  EXPECT_STREQ(f, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
  EXPECT_EQ(g, nullptr);

  free_many(7, &a, &b, &c, &d, &e, &f, &g);
}

TEST(reader, get_long) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%d\n%d", 1, 2);
  fprintf(test, "\n%ld %s\n\n", 12345678910, "hmm");
  rewind(test);

  long a, b, c;
  EXPECT_EQ(read_long(test, &a), 0);
  EXPECT_EQ(read_long(test, &b), 0);
  EXPECT_EQ(read_long(test, &c), 0);
  EXPECT_EQ(read_long(test, nullptr), PARSE_ERROR);
  EXPECT_EQ(read_long(test, nullptr), READ_ERROR);
  fclose(test);

  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 2);
  EXPECT_EQ(c, 12345678910);
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
