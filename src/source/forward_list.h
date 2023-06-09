// Copyright 2023 School-21

#ifndef SRC_SOURCE_FORWARDLIST_H_
#define SRC_SOURCE_FORWARDLIST_H_

#include <initializer_list>
#include <utility>

#include "container.h"
#include "list_node.h"

namespace s21 {

auto constexpr kEmptyCollectionMsg = "Empty Collection!";

template <class T>
class forward_list : public container<T> {
 public:
  using value_type = typename container<T>::value_type;
  using reference = typename container<T>::reference;
  using const_reference = typename container<T>::const_reference;
  using size_type = typename container<T>::size_type;

  forward_list() = default;
  forward_list(std::initializer_list<value_type> const &items);
  forward_list(const forward_list &q);
  forward_list(forward_list &&q) noexcept;
  ~forward_list() noexcept override;
  forward_list &operator=(const forward_list &q);
  forward_list &operator=(forward_list &&q) noexcept;

  [[nodiscard]] bool empty() const noexcept override;
  [[nodiscard]] size_type size() const noexcept override;

  void swap(forward_list &other);

 protected:
  const_reference front() const;
  const_reference back() const;

  virtual void push_back(const_reference value);
  virtual void push_front(const_reference value);
  virtual void pop_back();
  virtual void pop_front();

  virtual list_node<T> *allocate_node(value_type value) const;
  void clear() noexcept;

  list_node<T> *head_ = nullptr;
  list_node<T> *tail_ = nullptr;
  size_type size_ = 0;
};

template <class T>
forward_list<T>::forward_list(const std::initializer_list<value_type> &items) {
  for (const auto &i : items) {
    this->push_back(i);  // size calculated here
  }
}

template <class T>
forward_list<T>::forward_list(const forward_list<T> &q) {
  *this = q;
}

template <class T>
forward_list<T>::forward_list(forward_list<T> &&q) noexcept {
  *this = std::move(q);
}

template <class T>
forward_list<T>::~forward_list() noexcept {
  this->clear();
}

template <class T>
forward_list<T> &forward_list<T>::operator=(const forward_list<T> &q) {
  if (this == &q) {
    return *this;
  }

  size_ = q.size_;
  for (list_node<T> *temp = q.head_; temp != nullptr; temp = temp->get_next()) {
    push(temp->value());
  }

  return *this;
}

template <class T>
forward_list<T> &forward_list<T>::operator=(forward_list<T> &&q) noexcept {
  if (this == &q) {
    return *this;
  }

  this->clear();

  this->head_ = std::exchange(q.head_, nullptr);
  this->tail_ = std::exchange(q.tail_, nullptr);
  this->size_ = std::exchange(q.size_, 0);

  return *this;
}

template <class T>
bool forward_list<T>::empty() const noexcept {
  return head_ == nullptr;
}

template <class T>
typename forward_list<T>::size_type forward_list<T>::size() const noexcept {
  return size_;
}

template <class T>
void forward_list<T>::swap(forward_list &other) {
  std::swap(*this, other);
}

template <class T>
typename forward_list<T>::const_reference forward_list<T>::front() const {
  if (head_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }
  return head_->value();
}

template <class T>
typename forward_list<T>::const_reference forward_list<T>::back() const {
  if (tail_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }
  return tail_->value();
}

template <class T>
void forward_list<T>::push_back(const_reference value) {
  list_node<T> *new_node = allocate_node(value);
  ++size_;

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    tail_->set_next(new_node);
    tail_ = new_node;
  }
}

template <class T>
void forward_list<T>::push_front(const_reference value) {
  list_node<T> *new_node = allocate_node(value);
  ++size_;

  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    new_node->set_next(head_);
    head_ = new_node;
  }
}

template <class T>
void forward_list<T>::pop_back() {
  if (tail_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }

  --size_;
  list_node<T> *temp = head_;
  for (; temp->get_next() != tail_; temp = temp->get_next()) {
  }
  tail_ = temp;
  delete tail_->get_next();
  tail_->set_next(nullptr);
}

template <class T>
void forward_list<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::logic_error(kEmptyCollectionMsg);
  }

  --size_;
  list_node<T> *temp = head_;
  head_ = head_->get_next();
  delete temp;
}

template <class T>
list_node<T> *forward_list<T>::allocate_node(value_type value) const {
  list_node<T> *new_node = nullptr;

  try {
    new_node = new unary_node<T>(value);
  } catch (std::bad_alloc &e) {
    std::throw_with_nested(e);
  }

  return new_node;
}

template <class T>
void forward_list<T>::clear() noexcept {
  for (list_node<T> *temp = head_; temp != nullptr; temp = head_) {
    head_ = head_->get_next();
    delete temp;
  }
  this->head_ = nullptr;
  this->tail_ = nullptr;
  this->size_ = 0;
}

}  // namespace s21

#endif  // SRC_SOURCE_FORWARDLIST_H_
