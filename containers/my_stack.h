#ifndef MY_STACK_H_
#define MY_STACK_H_

#include <iostream>

using std::cout;
using std::endl;

namespace my {

template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  /*------ Constructors & Destructor ------*/
  Stack();
  explicit Stack(std::initializer_list<value_type> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s);
  ~Stack();

  Stack &operator=(const Stack &s);
  Stack &operator=(Stack &&s);

  /*------ Stack Element Access ------*/
  const_reference top() const;

  /*------ Stack Capacity ------*/
  bool empty();
  size_type size();

  /*------ Stack Modifiers ------*/
  void push(const_reference value);
  void pop();
  void swap(Stack &other) noexcept;

  /*------ Bonus Methods ------*/
  template <class... Args>
  void emplace_front(Args &&...args);

  /*------ Helping Methods ------*/
  void ShowFromTop();
  void Clear();

 private:
  class Node {
   public:
    value_type node_data_;
    Node *prev_node_;
    Node() : node_data_(), prev_node_(nullptr) {}
    // node for emplace methods
    template <class... Args>
    explicit Node(Args &&...args)
        : node_data_(std::forward<Args>(args)...), prev_node_(nullptr) {}
  };
  Node *Top_;
};

template <typename value_type>
Stack<value_type>::Stack() : Top_(nullptr) {}

template <typename value_type>
Stack<value_type>::Stack(std::initializer_list<value_type> const &items)
    : Stack() {
  for (auto element : items) {
    push(element);
  }
}

template <typename value_type>
Stack<value_type>::~Stack() {
  while (Top_) pop();
}

template <typename value_type>
Stack<value_type>::Stack(const Stack &s) : Stack() {
  *this = s;
}

template <typename value_type>
Stack<value_type>::Stack(Stack &&s) : Stack() {
  *this = std::move(s);
}

template <typename value_type>
Stack<value_type> &Stack<value_type>::operator=(const Stack &s) {
  if (this == &s)
    throw std::out_of_range("Coping the same Stack is forbidden!");
  Clear();
  Stack<value_type> temp_Stack;
  Node *temp_from_s = s.Top_;
  while (temp_from_s) {
    temp_Stack.push(temp_from_s->node_data_);
    temp_from_s = temp_from_s->prev_node_;
  }
  Node *temp = temp_Stack.Top_;
  while (temp) {
    push(temp->node_data_);
    temp = temp->prev_node_;
  }
  return *this;
}

template <typename value_type>
Stack<value_type> &Stack<value_type>::operator=(Stack &&s) {
  this->swap(s);
  s.Clear();
  return *this;
}

template <typename value_type>
typename Stack<value_type>::const_reference Stack<value_type>::top() const {
  if (Top_ == nullptr)
    throw std::out_of_range("Stack is empty!Top is impossible");
  return Top_->node_data_;
}

template <typename value_type>
bool Stack<value_type>::empty() {
  return (Top_ == nullptr);
}

template <typename value_type>
typename Stack<value_type>::size_type Stack<value_type>::size() {
  size_type count = 0;
  Node *temp = Top_;
  while (temp) {
    ++count;
    temp = temp->prev_node_;
  }
  return count;
}

template <typename value_type>
void Stack<value_type>::push(const_reference value) {
  Node *temp(new Node);
  temp->node_data_ = value;
  if (Top_) {
    temp->prev_node_ = Top_;
  }
  Top_ = temp;
}

template <typename value_type>
void Stack<value_type>::pop() {
  if (empty() == false) {
    Node *temp = Top_;
    if (size() == 1)
      Top_ = nullptr;
    else
      Top_ = temp->prev_node_;
    delete temp;
    temp = nullptr;
  }
}

template <typename value_type>
void Stack<value_type>::swap(Stack &other) noexcept {
  if (this != &other) {
    std::swap(this->Top_, other.Top_);
  }
}

template <typename value_type>
template <class... Args>
void Stack<value_type>::emplace_front(Args &&...args) {
  Node *temp = new Node(std::forward<Args>(args)...);
  if (Top_) {
    temp->prev_node_ = Top_;
  }
  Top_ = temp;
}

template <typename value_type>
void Stack<value_type>::ShowFromTop() {
  cout << "Input of MY Stack:" << endl;
  Node *temp = Top_;
  while (temp) {
    cout << temp->node_data_ << endl;
    temp = temp->prev_node_;
  }
}

template <typename value_type>
void Stack<value_type>::Clear() {
  while (empty() == false) pop();
}

}  // namespace my

#endif  //  MY_STACK_H_
