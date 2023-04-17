#ifndef CPP2_S21_CONTAINERS_1_FORWARDLIST_H
#define CPP2_S21_CONTAINERS_1_FORWARDLIST_H

#include <initializer_list>
#include <limits>
#include <utility>

#include "Container.h"
#include "Node.h"

namespace s21 {

auto constexpr kEmptyCollectionMsg = "Empty Collection!";

template <class T>
class ForwardList : public Container<T> {
 public:
  using value_type = typename Container<T>::value_type;
  using reference = typename Container<T>::reference;
  using const_reference = typename Container<T>::const_reference;
  using size_type = typename Container<T>::size_type;

  ForwardList() = default;
  ForwardList(std::initializer_list<value_type> const &items);
  ForwardList(const ForwardList &q);
  ForwardList(ForwardList &&q) noexcept;
  ~ForwardList() noexcept override;
  ForwardList &operator=(const ForwardList &q);
  ForwardList &operator=(ForwardList &&q) noexcept;

  [[nodiscard]] bool empty() const noexcept override;
  [[nodiscard]] size_type size() const noexcept override;

  void swap(ForwardList &other);

 protected:
  const_reference front() const;
  const_reference back() const;

  void push_back(const_reference value);
  void push_front(const_reference value);
  virtual void pop_back();
  void pop_front();

  virtual INode<T> *allocate_node(value_type value) const;
  void clear() noexcept;

  INode<T> *head_ = nullptr;
  INode<T> *tail_ = nullptr;
  size_type size_ = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_FORWARDLIST_H