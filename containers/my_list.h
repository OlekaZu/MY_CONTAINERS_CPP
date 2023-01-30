#ifndef MY_LIST_H_
#define MY_LIST_H_

#include <iostream>
#include <limits>

using std::cout;
using std::endl;

namespace my {

template <typename T>
class List {
  class Node;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator {
   public:
    ListIterator() : current_node_(nullptr) {}
    explicit ListIterator(Node* ptr_node) : current_node_(ptr_node) {}

    Node* GetCurrentNode() { return current_node_; }
    ListIterator& operator++() {
      current_node_ = current_node_->next_node_;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator tmp(*this);
      current_node_ = current_node_->next_node_;
      return tmp;
    }
    ListIterator& operator--() {
      current_node_ = current_node_->prev_node_;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator tmp(*this);
      current_node_ = current_node_->prev_node_;
      return tmp;
    }
    const_reference operator*() { return current_node_->node_data_; }

    bool operator==(const ListIterator& other) {
      return this->current_node_ == other.current_node_;
    }

    bool operator!=(const ListIterator& other) {
      return this->current_node_ != other.current_node_;
    }

   private:
    Node* current_node_;
  };

  using iterator = ListIterator;
  using const_iterator = const ListIterator;

  /*------ Constructors & Destructor ------*/
  List();
  explicit List(size_type n);
  explicit List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l);
  ~List();
  List& operator=(const List& l);
  List& operator=(List&& l);

  /*------ List Iterators ------*/
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  /*------ List Element Access ------*/
  const_reference front();
  const_reference back();

  /*------ List Capacity ------*/
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  /*------ List Modifiers ------*/
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List& other) noexcept;
  void merge(List& other);
  void splice(const_iterator pos, List& other);
  void reverse() noexcept;
  void unique();
  void sort();

  /*------ Bonus Methods ------*/
  template <class... Args>
  iterator emplace(const_iterator pos, Args&&... args);
  template <class... Args>
  void emplace_back(Args&&... args);
  template <class... Args>
  void emplace_front(Args&&... args);

  /*------ Helping Methods ------*/
  void ShowFromHead();

 private:
  class Node {
   public:
    value_type node_data_;
    Node* prev_node_;
    Node* next_node_;
    Node() : node_data_(), prev_node_(nullptr), next_node_(nullptr) {}
    // node for emplace methods
    template <class... Args>
    explicit Node(Args&&... args)
        : node_data_(std::forward<Args>(args)...),
          prev_node_(nullptr),
          next_node_(nullptr) {}
  };
  Node* Head_;
  Node* Tail_;
  Node* After_Tail_;

  /*------ Helping Methods ------*/
  void PushBack(Node* temp);
  void PushFront(Node* temp);
};

template <typename value_type>
List<value_type>::List() : Head_(nullptr), Tail_(nullptr) {
  After_Tail_ = new Node;
}

template <typename value_type>
List<value_type>::List(size_type n) : List() {
  if (n >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  if (n) {
    for (size_type i = 0; i < n; ++i) {
      Node* temp(new Node);
      PushBack(temp);
    }
  }
}

template <typename value_type>
List<value_type>::List(std::initializer_list<value_type> const& items)
    : List() {
  for (auto element : items) {
    push_back(element);
  }
}

template <typename value_type>
List<value_type>::List(const List& l) : List() {
  *this = l;
}

template <typename value_type>
List<value_type>::List(List&& l) : List() {
  *this = std::move(l);
}

template <typename value_type>
List<value_type>::~List() {
  clear();
  delete After_Tail_;
  After_Tail_ = nullptr;
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(const List& l) {
  if (this == &l) throw std::out_of_range("Coping the same list is forbidden!");
  clear();
  for (auto it = l.cbegin(); it != l.cend(); ++it) this->push_back(*it);
  return *this;
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(List&& l) {
  this->swap(l);
  l.clear();
  return *this;
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::begin() noexcept {
  if (Head_)
    return iterator(Head_);
  else
    return iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::end() noexcept {
  return iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::cbegin()
    const noexcept {
  if (Head_)
    return const_iterator(Head_);
  else
    return const_iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_iterator List<value_type>::cend()
    const noexcept {
  return const_iterator(After_Tail_);
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::front() {
  if (!size()) throw std::out_of_range("List is empty!");
  iterator first_node = begin();
  return *first_node;
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::back() {
  if (!size()) throw std::out_of_range("List is empty!");
  iterator last_node = end();
  --last_node;
  return *last_node;
}

template <typename value_type>
bool List<value_type>::empty() const noexcept {
  return (Head_ == nullptr && Tail_ == nullptr);
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::size() const noexcept {
  size_type count = 0;
  for (auto it = cbegin(); it != cend(); ++it) ++count;
  return count;
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::max_size()
    const noexcept {
  size_type max_size =
      (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  return max_size;
}

template <typename value_type>
void List<value_type>::clear() {
  while (empty() == false) pop_front();
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::insert(
    iterator pos, const_reference value) {
  Node* pos_node = pos.GetCurrentNode();
  iterator inserted_pos;
  if (pos_node == Head_ || empty() == true) {
    push_front(value);
    inserted_pos = begin();
  } else {
    --pos;
    Node* previous_node = pos.GetCurrentNode();
    Node* inserted_node(new Node);
    inserted_node->node_data_ = value;
    inserted_node->next_node_ = pos_node;
    inserted_node->prev_node_ = previous_node;
    pos_node->prev_node_ = inserted_node;
    previous_node->next_node_ = inserted_node;
    iterator inserted_pos_tmp(inserted_node);
    inserted_pos = inserted_pos_tmp;
  }
  return inserted_pos;
}

template <typename value_type>
void List<value_type>::erase(iterator pos) {
  if (empty() == true)
    throw std::out_of_range("List is empty! Nothing to be erased");
  Node* pos_node = pos.GetCurrentNode();
  if (pos_node == After_Tail_)
    throw std::out_of_range("The past-the-last element cannot be erased.");
  if (pos_node == Head_) {
    pop_front();
  } else if (pos_node == Tail_) {
    pop_back();
  } else {
    --pos;
    Node* previous_node = pos.GetCurrentNode();
    previous_node->next_node_ = pos_node->next_node_;
    (pos_node->next_node_)->prev_node_ = previous_node;
    delete pos_node;
    pos_node = nullptr;
  }
}

template <typename value_type>
void List<value_type>::push_back(const_reference value) {
  Node* temp(new Node);
  temp->node_data_ = value;
  PushBack(temp);
}

template <typename value_type>
void List<value_type>::push_front(const_reference value) {
  if (size() >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  Node* temp(new Node);
  temp->node_data_ = value;
  PushFront(temp);
}

template <typename value_type>
void List<value_type>::pop_back() {
  if (!size()) throw std::out_of_range("List is empty!Pop_back is impossible");
  Node* temp = nullptr;
  temp = Tail_;
  if (size() == 1) {
    Head_ = nullptr;
    Tail_ = nullptr;
  } else {
    Tail_ = temp->prev_node_;
    Tail_->next_node_ = After_Tail_;
  }
  delete temp;
  temp = nullptr;
}

template <typename value_type>
void List<value_type>::pop_front() {
  if (!size()) throw std::out_of_range("List is empty!Pop_back is impossible");
  Node* temp = nullptr;
  temp = Head_;
  if (size() == 1) {
    Head_ = nullptr;
    Tail_ = nullptr;
  } else {
    Head_ = temp->next_node_;
    Head_->prev_node_ = After_Tail_;
    After_Tail_->next_node_ = Head_;
  }
  delete temp;
  temp = nullptr;
}

template <typename value_type>
void List<value_type>::swap(List& other) noexcept {
  if (this != &other) {
    std::swap(this->Head_, other.Head_);
    std::swap(this->Tail_, other.Tail_);
    std::swap(this->After_Tail_, other.After_Tail_);
  }
}

template <typename value_type>
void List<value_type>::merge(List& other) {
  if (this != &other && other.empty() == false) {
    auto it = cbegin();
    auto it_other = other.cbegin();
    while (it_other != other.cend()) {
      if (*it >= *it_other) {
        insert(it, *it_other);
        ++it_other;
      } else if (it.GetCurrentNode() != Tail_) {
        ++it;
      } else {
        push_back(*it_other);
        ++it_other;
      }
    }
    other.clear();
  }
}

template <typename value_type>
void List<value_type>::splice(const_iterator pos, List& other) {
  if (this == &other)
    throw std::out_of_range("Splice the same list is forbidden!");
  if (other.empty() == false) {
    for (auto it_other = other.cbegin(); it_other != other.cend(); ++it_other)
      insert(pos, *it_other);
    other.clear();
  }
}

template <typename value_type>
void List<value_type>::reverse() noexcept {
  if (empty() == false) {
    for (auto it = cbegin(); it != cend();) {
      Node* temp = it.GetCurrentNode();
      ++it;
      std::swap(temp->next_node_, temp->prev_node_);
    }
    std::swap(Head_, Tail_);
    std::swap(After_Tail_->next_node_, After_Tail_->prev_node_);
  }
}

template <typename value_type>
void List<value_type>::unique() {
  if (empty() == false) {
    for (auto it = cbegin(); it != cend();) {
      iterator where_is_first_compare_element = it;
      value_type current_element = *it;
      value_type next_element = *(++it);
      Node* next_point_to_node = it.GetCurrentNode();
      if (current_element == next_element &&
          next_point_to_node != After_Tail_) {
        erase(it);
        it = where_is_first_compare_element;
      }
    }
  }
}

template <typename value_type>
void List<value_type>::sort() {
  if (empty() == false) {
    iterator it_end = cend();
    iterator it_last_element = --it_end;
    ++it_end;
    for (auto it = cbegin(); it != it_end; ++it) {
      for (auto it2 = cbegin(); it2 != it_last_element;) {
        value_type current_element = *it2;
        Node* current_point_to_node = it2.GetCurrentNode();
        value_type next_element = *(++it2);
        Node* next_point_to_node = it2.GetCurrentNode();
        if (current_element > next_element && next_point_to_node != After_Tail_)
          std::swap(current_point_to_node->node_data_,
                    next_point_to_node->node_data_);
      }
    }
  }
}

template <typename value_type>
template <class... Args>
typename List<value_type>::iterator List<value_type>::emplace(
    const_iterator pos, Args&&... args) {
  iterator copy_pos(pos);
  Node* pos_node = copy_pos.GetCurrentNode();
  iterator inserted_pos;
  if (pos_node == Head_ || empty() == true) {
    emplace_front(std::forward<Args>(args)...);
    inserted_pos = begin();
  } else {
    --copy_pos;
    Node* previous_node = copy_pos.GetCurrentNode();
    Node* inserted_node(new Node(std::forward<Args>(args)...));
    inserted_node->next_node_ = pos_node;
    inserted_node->prev_node_ = previous_node;
    pos_node->prev_node_ = inserted_node;
    previous_node->next_node_ = inserted_node;
    iterator inserted_pos_tmp(inserted_node);
    inserted_pos = inserted_pos_tmp;
  }
  return inserted_pos;
}

template <typename value_type>
template <class... Args>
void List<value_type>::emplace_back(Args&&... args) {
  Node* temp(new Node(std::forward<Args>(args)...));
  PushBack(temp);
}

template <typename value_type>
template <class... Args>
void List<value_type>::emplace_front(Args&&... args) {
  Node* temp(new Node(std::forward<Args>(args)...));
  PushFront(temp);
}

template <typename value_type>
void List<value_type>::ShowFromHead() {
  cout << "Input of MY List:" << endl;
  Node* temp = nullptr;
  temp = Head_;
  while (temp != After_Tail_ && temp) {
    cout << temp->node_data_ << endl;
    temp = temp->next_node_;
  }
}

template <typename value_type>
void List<value_type>::PushBack(Node* temp) {
  if (size() >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  temp->next_node_ = After_Tail_;
  After_Tail_->prev_node_ = temp;
  if (Head_) {
    temp->prev_node_ = Tail_;
    Tail_->next_node_ = temp;
    Tail_ = temp;
  } else {
    temp->prev_node_ = After_Tail_;
    Head_ = temp;
    Tail_ = temp;
  }
  After_Tail_->next_node_ = Head_;
}

template <typename value_type>
void List<value_type>::PushFront(Node* temp) {
  if (size() >= max_size())
    throw std::out_of_range("Limit of the container is exceeded");
  temp->prev_node_ = After_Tail_;
  After_Tail_->next_node_ = temp;
  if (Head_) {
    temp->next_node_ = Head_;
    Head_->prev_node_ = temp;
    Head_ = temp;
  } else {
    temp->next_node_ = After_Tail_;
    Head_ = temp;
    Tail_ = temp;
  }
  After_Tail_->prev_node_ = Tail_;
}

}  // namespace my

#endif  //  MY_LIST_H_
