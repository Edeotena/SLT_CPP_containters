// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <set>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool sets_equal(Set<T> first, std::set<T> second) {
  if (first.size() != second.size()) {
    return false;
  }
  auto first_it = first.begin();
  auto second_it = second.begin();
  for (; first_it != first.end() && second_it != second.end();
       ++first_it, ++second_it) {
    if (*first_it != *second_it) {
      return false;
    }
  }

  return first_it == first.end() && second_it == second.end();
}

TEST(SetSuite, default_contructor_test) {
  Set<int> my_set;
  std::set<int> std_set;
  ASSERT_TRUE(sets_equal(my_set, std_set));
}

TEST(SetSuite, initializer_list_constructor_test) {
  Set<int> my_set = {4, 2, 1, 1};
  std::set<int> std_set = {4, 2, 1, 1};

  ASSERT_TRUE(sets_equal(my_set, std_set));
}

TEST(SetSuite, copy_constructor_test) {
  Set<int> my_set = {4, 2, 1, 1};
  Set<int> my_copied(my_set);
  std::set<int> std_set = {4, 2, 1, 1};

  ASSERT_TRUE(sets_equal(my_copied, std_set));
}

TEST(SetSuite, move_constructor_test) {
  Set<int> my_set = {1, 2, 3};
  Set<int> my_moved(std::move(my_set));
  std::set<int> std_set = {1, 2, 3};
  std::set<int> std_moved(std::move(std_set));
  ASSERT_TRUE(sets_equal(my_moved, std_moved));
  ASSERT_TRUE(sets_equal(my_set, std_set));
}

TEST(SetSuite, begin_normal_test) {
  Set<int> my_set = {1};
  ASSERT_EQ(*my_set.begin(), 1);
}

TEST(SetSuite, end_normal_test) {
  Set<int> my_set = {1};
  ASSERT_EQ(*(--my_set.end()), 1);
}

TEST(SetSuite, equal_iterators_test) {
  Set<int> my_set;
  ASSERT_TRUE(my_set.begin() == my_set.end());
}

TEST(SetSuite, empty_list_test) {
  Set<int> my_set;
  ASSERT_TRUE(my_set.empty());
}

TEST(SetSuite, non_empty_list_test) {
  Set<int> my_set = {1, 2, 3};
  ASSERT_FALSE(my_set.empty());
}

TEST(SetSuite, zero_size_test) {
  Set<int> my_set;
  ASSERT_EQ(my_set.size(), 0);
}

TEST(SetSuite, non_zero_size_test) {
  for (int i = 0; i < 10; ++i) {
    Set<int> my_set;
    for (int j = 0; j < i; ++j) {
      my_set.insert(j);
    }
    ASSERT_EQ(my_set.size(), i);
  }
}

TEST(SetSuite, clear_empty_test) {
  Set<int> my_set;
  my_set.clear();
  ASSERT_TRUE(true);  // not sigsegv
}

TEST(SetSuite, clear_non_empty_test) {
  Set<int> my_set = {1, 2, 3};
  my_set.clear();

  ASSERT_EQ(my_set.size(), 0);
  ASSERT_TRUE(my_set.empty());
  ASSERT_TRUE(my_set.begin() == my_set.end());
}

TEST(SetSuite, insert_to_empty_test) {
  Set<int> a;
  auto res = a.insert(1);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), 1);
  ASSERT_TRUE(sets_equal(a, std::set{1}));
}

TEST(SetSuite, insert_to_non_empty_test) {
  Set<int> a = {1};
  auto res = a.insert(2);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*(res.first), 2);
  ASSERT_TRUE(sets_equal(a, std::set{1, 2}));
}

TEST(SetSuite, fail_insert_test) {
  Set<int> a = {1};
  auto res = a.insert(1);
  ASSERT_FALSE(res.second);
  ASSERT_EQ(res.first, a.end());
  ASSERT_TRUE(sets_equal(a, std::set{1}));
}

TEST(SetSuite, erase_empty_test) {
  Set<int> a;
  ASSERT_THROW(a.erase(a.begin()), std::out_of_range);
}

TEST(SetSuite, erase_start_test) {
  Set<int> a = {1, 2};
  a.erase(a.begin());

  ASSERT_EQ(*a.begin(), 2);
  ASSERT_TRUE(sets_equal(a, std::set<int>{2}));
}

TEST(SetSuite, erase_end_test) {
  Set<int> a = {1, 2};
  a.erase(a.end());

  ASSERT_EQ(*a.begin(), 1);
  ASSERT_TRUE(sets_equal(a, std::set<int>{1}));
}

TEST(SetSuite, erase_mid_test) {
  Set<int> a = {1, 2, 3};
  a.erase(++a.begin());

  ASSERT_EQ(*a.begin(), 1);
  ASSERT_EQ(*a.end(), 3);
  ASSERT_TRUE(sets_equal(a, std::set<int>{1, 3}));
}

}  // namespace s21
