#include <gtest/gtest.h>

#include "list.h"

TEST(ListTest, DefaultConstructor) {
  auto l = tlib::List<int>();
  ASSERT_EQ(l.size(), 0);
  ASSERT_TRUE(l.empty());
}

TEST(ListTest, SizeConstructor) {
  auto l = tlib::List<int>(10);
  ASSERT_EQ(l.size(), 10);
  ASSERT_FALSE(l.empty());
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(l.at(i), 0);
  }
}

TEST(ListTest, InitializerList) {
  tlib::List<int> l{1, 2, 3, 4, 5};
  ASSERT_EQ(l.size(), 5);
  ASSERT_EQ(l.at(0), 1);
  ASSERT_EQ(l.at(1), 2);
  ASSERT_EQ(l.at(2), 3);
  ASSERT_EQ(l.at(3), 4);
  ASSERT_EQ(l.at(4), 5);
}

TEST(ListTest, Copy) {
  tlib::List<int> l{1, 2, 3, 4, 5};
  // Copy constructor
  tlib::List<int> l2(l);
  ASSERT_EQ(l.size(), l2.size());
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(l.at(i), l2.at(i));
  }
  // Copy assignment
  tlib::List<int> l3 = l2;
  ASSERT_EQ(l.size(), l3.size());
  for (int i = 0; i < 5; i++) {
    ASSERT_EQ(l.at(i), l3.at(i));
  }
}

TEST(ListTest, Iterator) {
  tlib::List<int> l{0, 1, 2, 3, 4, 5};
  for (auto &v : l) {
  }
}

TEST(ListTest, FrontBack) {
  tlib::List<int> l{1, 2, 3, 4, 5};
  ASSERT_EQ(l.front(), 1);
  ASSERT_EQ(l.back(), 5);

  tlib::List<int> ll = {123};
  ASSERT_EQ(ll.front(), 123);
  ASSERT_EQ(ll.back(), 123);
}

TEST(ListTest, Push) {
  tlib::List<int> l;
  ASSERT_EQ(l.size(), 0);
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);
  ASSERT_EQ(l.size(), 3);
  ASSERT_EQ(l.at(0), 1);
  ASSERT_EQ(l.at(1), 2);
  ASSERT_EQ(l.at(2), 3);

  l.push_front(5);
  l.push_front(6);
  ASSERT_EQ(l.size(), 5);
  ASSERT_EQ(l.at(0), 6);
  ASSERT_EQ(l.at(1), 5);
}

TEST(ListTest, Pop) {
  tlib::List<int> l{1, 2, 3, 4, 5, 6, 7, 8};
  ASSERT_EQ(l.size(), 8);
  ASSERT_EQ(l.front(), 1);
  ASSERT_EQ(l.back(), 8);
  l.pop_back();
  ASSERT_EQ(l.back(), 7);
  l.pop_back();
  ASSERT_EQ(l.front(), 1);
  ASSERT_EQ(l.back(), 6);
  ASSERT_EQ(l.size(), 6);

  ASSERT_EQ(l.front(), 1);
  l.pop_front();
  ASSERT_EQ(l.front(), 2);
  ASSERT_EQ(l.size(), 5);
  l.pop_front();
  ASSERT_EQ(l.front(), 3);
  ASSERT_EQ(l.back(), 6);
  ASSERT_EQ(l.size(), 4);
}

TEST(ListTest, Erase) {
  tlib::List<int> l{1, 2, 3, 4, 5};
  ASSERT_EQ(l.size(), 5);
  l.erase();
  ASSERT_EQ(l.size(), 0);
}
