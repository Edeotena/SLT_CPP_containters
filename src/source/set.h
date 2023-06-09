// Copyright 2023 school-21

#ifndef SRC_SOURCE_SET_H_
#define SRC_SOURCE_SET_H_

#include <utility>

#include "bs_tree.h"

namespace s21 {

template <class V>
class set : public container<V> {
 private:
  struct KeyTreeNode;

 public:
  using value_type = V;
  using key_type = V;
  using iterator =
      typename bs_tree<KeyTreeNode, key_type, value_type>::iterator;
  using const_iterator =
      typename bs_tree<KeyTreeNode, key_type, value_type>::const_iterator;
  using reference = V &;
  using const_reference = const V &;
  using size_type = size_t;

  set() noexcept = default;
  set(std::initializer_list<value_type> const &items);
  set(const set &other);
  set(set &&other) noexcept;
  set &operator=(const set &s) noexcept;
  set &operator=(set &&s) noexcept;

  ~set() noexcept = default;

  iterator begin() const noexcept;
  iterator end() const noexcept;

  [[nodiscard]] bool empty() const noexcept override;
  [[nodiscard]] size_type size() const noexcept override;
  [[nodiscard]] size_type max_size() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other) noexcept;
  void merge(set &other);

  iterator find(const key_type &key) const noexcept;
  [[nodiscard]] bool contains(const key_type &key) const noexcept;

 private:
  struct KeyTreeNode {
   public:
    using value_type = V;
    [[nodiscard]] value_type key() const noexcept;
    KeyTreeNode() noexcept = default;
    KeyTreeNode(value_type value) noexcept;
    value_type value_ = value_type();
  };

  bs_tree<KeyTreeNode, key_type, value_type> tree_ =
      bs_tree<KeyTreeNode, key_type, value_type>();
};

template <class V>
set<V>::set(const set &other) {
  *this = other;
}

template <class V>
set<V>::set(set &&other) noexcept {
  *this = std::move(other);
}

template <class V>
set<V> &set<V>::operator=(const set &s) noexcept {
  tree_ = s.tree_;
  return *this;
}

template <class V>
set<V> &set<V>::operator=(set &&s) noexcept {
  tree_ = std::move(s.tree_);
  return *this;
}

template <class V>
typename set<V>::iterator set<V>::begin() const noexcept {
  return tree_.begin();
}

template <class V>
typename set<V>::iterator set<V>::end() const noexcept {
  return tree_.end();
}

template <class V>
bool set<V>::empty() const noexcept {
  return size() == 0;
}

template <class V>
typename set<V>::size_type set<V>::size() const noexcept {
  return tree_.size();
}

template <class V>
typename set<V>::size_type set<V>::max_size() const noexcept {
  return tree_.max_size();
}

template <class V>
void set<V>::clear() noexcept {
  tree_.clear();
}

template <class V>
void set<V>::erase(set::iterator pos) {
  tree_.erase(pos);
}

template <class V>
void set<V>::swap(set &other) noexcept {
  tree_.swap(other.tree_);
}

template <class V>
void set<V>::merge(set &other) {
  set<V> res;
  for (auto elem = other.begin(); elem != other.end(); ++elem) {
    if (!insert(*elem).second) {
      res.insert(*elem);
    }
  }
  other = res;
}

template <class V>
bool set<V>::contains(const key_type &key) const noexcept {
  return tree_.contains(key);
}

template <class V>
typename set<V>::iterator set<V>::find(const key_type &key) const noexcept {
  return tree_.find(key);
}

template <class V>
[[nodiscard]] typename set<V>::value_type set<V>::KeyTreeNode::key()
    const noexcept {
  return value_;
}

template <class V>
set<V>::KeyTreeNode::KeyTreeNode(value_type value) noexcept : value_(value) {}

template <class V>
std::pair<typename set<V>::iterator, bool> set<V>::insert(
    const value_type &value) {
  if (!contains(value)) {
    return std::pair<iterator, bool>(tree_.insert(value), true);
  }
  return std::pair<iterator, bool>(tree_.end(), false);
}

template <class V>
set<V>::set(std::initializer_list<value_type> const &items) {
  for (auto elem : items) {
    insert(elem);
  }
}

}  // namespace s21
#endif  // SRC_SOURCE_SET_H_
