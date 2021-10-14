#include <gtest/gtest.h>

extern "C" {
#include "IO.h"
#include "utils.h"
}

TEST(reader, get_line) {
  FILE *test = fopen("test.txt", "w+");
  ASSERT_NE(test, nullptr);
  fprintf(test, "%s\n%s", "Hello, world!", "That's a test!");
  fprintf(test, "\n%s\n\n",
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
  fprintf(test, "\n%s\n\n",
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
