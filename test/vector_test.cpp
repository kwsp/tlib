#include <gtest/gtest.h>

#include "vector.h"

TEST(VectorTestConstructor, DefaultConstructor) {
  ASSERT_NO_FATAL_FAILURE(tlib::Vector<int>());
}

TEST(VectorTestConstructor, SizeConstructor) {
  auto v = tlib::Vector<int>(100);
  ASSERT_EQ(v.size(), 100);
}

TEST(VectorTestConstructor, DefaultValue) {
  auto v = tlib::Vector<int>(10, 123);
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(v[i], 123);
  }
}

TEST(VectorTestConstructor, InitializerList) {
  tlib::Vector<int> v = {1, 4, 3, 2, 5};
  ASSERT_EQ(v[0], 1);
  ASSERT_EQ(v[1], 4);
  ASSERT_EQ(v[2], 3);
  ASSERT_EQ(v[3], 2);
  ASSERT_EQ(v[4], 5);
  ASSERT_EQ(v.size(), 5);

  tlib::Vector<int> v1{1, 2, 5, 4, 3};
  ASSERT_EQ(v1[2], 5);
  ASSERT_EQ(v1[3], 4);
  ASSERT_EQ(v1[4], 3);
}

TEST(VectorTestConstructor, CopyConstructor) {
  tlib::Vector<int> v1 = {4, 3, 2, 1};
  auto v2 = tlib::Vector<int>(v1);
  ASSERT_EQ(v1.size(), v2.size());
  for (int i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTestConstructor, CopyAssignment) {
  tlib::Vector<int> v1 = {4, 3, 2, 1};
  auto v2 = v1;
  ASSERT_EQ(v1.size(), v2.size());
  for (int i = 0; i < v1.size(); i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTestCapacity, IsEmptyInitially) {
  auto v = tlib::Vector<int>();
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.size(), 0);
}

TEST(VectorTestCapacity, SizeResize) {
  auto v = tlib::Vector<int>(10);
  ASSERT_EQ(v.size(), 10);
  v.resize(100);
  ASSERT_EQ(v.size(), 100);
}

TEST(VectorTestCapacity, Shrink) {
  auto v = tlib::Vector<int>(10, 1);

  v.push_back(11);
  v.push_back(12);
  ASSERT_EQ(v.size(), 12);
  v.shrink_to_fit();
  ASSERT_EQ(v.size(), 12);
}

class VectorTestFixture : public ::testing::Test {
protected:
  void SetUp() override {
    for (int i = 0; i < 3; i++) {
      v1_.push_back(i);
    }

    for (int i=0; i<100; i++) {
      v2_.push_back(i);
    }
  }


  tlib::Vector<int> v0_;
  tlib::Vector<int> v1_;
  tlib::Vector<int> v2_;
};

TEST_F(VectorTestFixture, ElementAccessOperator) {
  for (int i = 0; i < 3; ++i)
    ASSERT_EQ(v1_[i], i);
}

TEST_F(VectorTestFixture, Front) {
  ASSERT_EQ(v1_.front(), 0);
  ASSERT_EQ(v1_.back(), v1_.size() - 1);

  tlib::Vector<int> v;
  ASSERT_ANY_THROW(v.front());
  ASSERT_ANY_THROW(v.back());
}

// TODO: Test iterators

TEST(VectorTest, Resize) {
  tlib::Vector<int> v;
  ASSERT_EQ(v.size(), 0);
  v.resize(100);
  ASSERT_EQ(v.size(), 100);
}

TEST(VectorTest, PushBack) {
  tlib::Vector<int> v;
  for (int i = 0; i < 1000; i++) {
    v.push_back(i);
  }
  ASSERT_EQ(v.size(), 1000);
  ASSERT_GE(v.size(), 1000);
  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ(v[i], i);
  }
}

