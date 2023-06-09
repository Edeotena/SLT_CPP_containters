// Copyright 2023 School-21

#include <gtest/gtest.h>

#include <stack>

#include "../s21_containers.h"

namespace s21 {

template <class T>
bool stacks_equal(stack<T> first, stack<T> second) {
  while (!first.empty() && !second.empty()) {
    T first_elem = first.top();
    T second_elem = second.top();

    T first_copy = first_elem;
    T second_copy = second_elem;
    if (first_copy != second_copy) {
      return false;
    }

    first.pop();
    second.pop();
  }

  return first.empty() && second.empty();
}

template <class T>
bool stacks_equal(stack<T> first, std::stack<T> second) {
  while (!first.empty() && !second.empty()) {
    T first_elem = first.top();
    T second_elem = second.top();

    T first_copy = first_elem;
    T second_copy = second_elem;
    if (first_copy != second_copy) {
      return false;
    }

    first.pop();
    second.pop();
  }

  return first.empty() && second.empty();
}

TEST(StackSuite, default_constructor_test) {
  std::stack<int> std_stack;
  stack<int> my_stack;

  ASSERT_TRUE(my_stack.empty());
  ASSERT_EQ(my_stack.empty(), std_stack.empty());

  ASSERT_EQ(std_stack.size(), 0);
  ASSERT_EQ(std_stack.size(), my_stack.size());

  ASSERT_THROW(my_stack.top(), std::logic_error);
}

TEST(StackSuite, initializer_constructor_test) {
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);

  stack<int> my_stack = {1, 2};

  ASSERT_EQ(my_stack.top(), 2);
  ASSERT_EQ(std_stack.top(), my_stack.top());

  std_stack.pop();
  my_stack.pop();

  ASSERT_EQ(my_stack.top(), 1);
  ASSERT_EQ(std_stack.top(), my_stack.top());
}

TEST(StackSuite, copy_constructor_test) {
  std::stack<int> std_base;
  std_base.push(1);
  std_base.push(2);
  std_base.push(3);
  std::stack<int> std_res(std_base);

  stack<int> my_base = {1, 2, 3};
  stack<int> my_res(my_base);

  ASSERT_TRUE(stacks_equal(my_base, my_res));
  ASSERT_TRUE(stacks_equal(my_res, std_res));
}

TEST(StackSuite, move_constructor_test) {
  std::stack<int> std_base;
  std_base.push(1);
  std_base.push(2);
  std_base.push(3);
  std::stack<int> std_res(std::move(std_base));

  stack<int> my_base = {1, 2, 3};
  stack<int> my_res(std::move(my_base));

  ASSERT_TRUE(my_base.empty());
  ASSERT_TRUE(stacks_equal(my_res, std_res));
}

TEST(StackSuite, present_top_test) {
  stack<int> my_stack = {1, 2};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);

  ASSERT_EQ(my_stack.top(), 2);
  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(StackSuite, missing_top_test) {
  stack<int> my_stack;
  ASSERT_THROW(my_stack.top(), std::logic_error);
}

TEST(StackSuite, empty_stack_test) {
  stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_TRUE(my_stack.empty());
  ASSERT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(StackSuite, non_empty_stack_test) {
  stack<int> my_stack = {1};
  std::stack<int> std_stack;
  std_stack.push(1);

  ASSERT_FALSE(my_stack.empty());
  ASSERT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(StackSuite, non_zero_size_test) {
  stack<int> my_stack = {1, 2, 3};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);

  ASSERT_EQ(my_stack.size(), 3);
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackSuite, zero_size_test) {
  stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_EQ(my_stack.size(), 0);
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackSuite, push_to_empty_test) {
  stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_THROW(my_stack.top(), std::logic_error);

  my_stack.push(1);
  std_stack.push(1);

  ASSERT_EQ(my_stack.size(), 1);
  ASSERT_EQ(my_stack.top(), 1);
  ASSERT_EQ(my_stack.top(), std_stack.top());
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackSuite, push_to_non_empty_test) {
  stack<int> my_stack = {1};
  std::stack<int> std_stack;
  std_stack.push(1);

  my_stack.push(2);
  std_stack.push(2);

  ASSERT_EQ(my_stack.size(), 2);
  ASSERT_EQ(my_stack.top(), 2);
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackSuite, pop_non_empty_test) {
  stack<int> my_stack = {1, 2};
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);

  ASSERT_EQ(my_stack.top(), 2);
  ASSERT_EQ(my_stack.top(), std_stack.top());

  my_stack.pop();
  std_stack.pop();

  ASSERT_EQ(my_stack.size(), 1);
  ASSERT_EQ(my_stack.top(), 1);
  ASSERT_EQ(my_stack.top(), std_stack.top());
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(StackSuite, pop_empty_test) {
  stack<int> my_stack;
  ASSERT_THROW(my_stack.pop(), std::logic_error);
}

TEST(StackSuite, swap_test) {
  stack<int> first_stack = {1, 2, 3};
  stack<int> second_stack = {4, 5, 6};
  stack<int> first_copy(first_stack);
  stack<int> second_copy(second_stack);

  first_stack.swap(second_stack);
  ASSERT_TRUE(stacks_equal(first_stack, second_copy));
  ASSERT_TRUE(stacks_equal(second_stack, first_copy));
}

}  // namespace s21
