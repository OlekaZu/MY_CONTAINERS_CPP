#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

#include <iostream>

#include "my_list.h"
using std::cout;
using std::endl;

namespace my {
template <typename T>
class Queue : private List<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /*------ Constructors & Destructor ------*/
  Queue() : List<value_type>::List() {}
  explicit Queue(std::initializer_list<value_type> const &items)
      : List<value_type>::List(items) {}
  Queue(const Queue &s) : List<value_type>::List(s) {}
  Queue(Queue &&s) : List<value_type>::List(std::move(s)) {}
  ~Queue() {}

  Queue &operator=(const Queue &s) {
    if (this == &s)
      throw std::out_of_range("Coping the same Queue is forbidden!");
    List<value_type>::clear();
    for (auto it = s.cbegin(); it != s.cend(); ++it) this->push_back(*it);
    return *this;
  }
  Queue &operator=(Queue &&s) {
    List<value_type>::operator=(std::move(s));
    return *this;
  }

  /*------ Queue Element Access ------*/
  const_reference front() {
    if (!size()) throw std::out_of_range("Queue is empty!");
    auto first_node = List<value_type>::begin();
    return *first_node;
  }
  const_reference back() {
    if (!size()) throw std::out_of_range("Queue is empty!");
    auto last_node = List<value_type>::end();
    --last_node;
    return *last_node;
  }

  /*------ Queue Capacity ------*/
  using List<value_type>::empty;
  using List<value_type>::size;

  /*------ Queue Modifiers ------*/
  void push(const_reference value) { List<value_type>::push_back(value); }
  void pop() { List<value_type>::pop_front(); }
  void swap(Queue &other) noexcept { List<value_type>::swap(other); }

  /*------ Bonus Method ------*/
  // template <class... Args>
  using List<value_type>::emplace_back;

  /*------ Helping Methods ------*/
  void ShowFromHead() {
    cout << "Input of My Queue from list:" << endl;
    List<value_type>::ShowFromHead();
  }
};

}  // namespace my

#endif  //  MY_QUEUE_H_
