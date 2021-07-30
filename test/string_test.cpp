#include <gtest/gtest.h>

#include "tlib/string.h"

using tlib::String;

TEST(StringTestConstructor, Simple) {
  String str("Hello world");
  ASSERT_EQ(str.size(), 11);
}

TEST(StringTestConstructor, Move) {
  String s1("Hello world");
  const char *ptr1 = static_cast<const char *>(s1);
  String s2 = std::move(s1);
  const char *ptr2 = static_cast<const char *>(s2);
  ASSERT_EQ(ptr1, ptr2);
  ASSERT_EQ(static_cast<const char *>(s1), nullptr);
}

TEST(StringOps, Equality) {
  String s1("hello");
  String s2("hello");
  String s3("boo");
  ASSERT_TRUE(s1 == s2);
  ASSERT_TRUE(s1 != s3);
  ASSERT_TRUE(s3 == "boo");
  ASSERT_TRUE(s3 != "b");
}

TEST(StringOps, StringConcat) {
  String s1("abc");
  String s2("def");
  auto s3 = s1 + s2;
  ASSERT_EQ(s3.size(), 6);
  ASSERT_EQ(s3, "abcdef");
}

TEST(StringOps, Subscript) {
  String s1("abcd");
  ASSERT_EQ(s1[0], 'a');
  ASSERT_EQ(s1[1], 'b');
  ASSERT_EQ(s1[2], 'c');
  ASSERT_EQ(s1[3], 'd');
  ASSERT_ANY_THROW(s1[4]);
}
