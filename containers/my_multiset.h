#ifndef MY_MULTISET_H_
#define MY_MULTISET_H_

#include "my_set.h"

namespace my {
template <typename Key>
class MultiSet : public Set<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using iterator = typename Set<Key>::iterator;
  using const_iterator = typename Set<Key>::const_iterator;

  /*------ Constructors & Destructor ------*/
  MultiSet() {}
  explicit MultiSet(std::initializer_list<value_type> const& items)
      : MultiSet() {
    for (auto element : items) insert(element);
  }
  MultiSet(const MultiSet& m) : MultiSet() { *this = m; }
  MultiSet(MultiSet&& m) : MultiSet() { *this = std::move(m); }
  ~MultiSet() {}

  MultiSet& operator=(const MultiSet& m) {
    if (this == &m) throw std::out_of_range("Coping the same Set isforbidden!");
    Set<Key>::clear();
    for (auto it = m.cbegin(); it != m.cend(); ++it) this->insert(*it);
    return *this;
  }
  MultiSet& operator=(MultiSet&& m) {
    Set<Key>::operator=(std::move(m));
    return *this;
  }

  /*------ MultiSet Iterators ------*/
  using Set<Key>::begin;
  using Set<Key>::end;
  using Set<Key>::cbegin;
  using Set<Key>::cend;

  /*------ MultiSet Capacity ------*/
  using Set<Key>::empty;
  using Set<Key>::size;
  using Set<Key>::max_size;

  /*------ MultiSet Modifiers ------*/
  using Set<Key>::clear;

  iterator insert(const value_type& value);

  using Set<Key>::erase;
  using Set<Key>::swap;
  void merge(MultiSet& other);

  /*------ MultiSet Lookup ------*/
  size_type count(const Key& key);
  using Set<Key>::contains;
  using Set<Key>::find;
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  /*------ Bonus Methods ------*/
  template <class... Args>
  iterator emplace(Args&&... args);

  /*------ Helping Methods ------*/
  using Set<Key>::ShowSetSort;

 private:
  using Node = typename Set<Key>::Node;
  using Set<Key>::root_;
  using Set<Key>::after_last_;

  /*------ Helping Methods ------*/
  iterator InsertNode(Node* insert_node);
};

template <typename key_type>
typename MultiSet<key_type>::iterator MultiSet<key_type>::insert(
    const_reference value) {
  if ((size() + 1) > max_size()) throw std::out_of_range("Limit is exceeded");
  Node* insert_node(new Node(value));
  return InsertNode(insert_node);
}

template <typename key_type>
typename MultiSet<key_type>::iterator MultiSet<key_type>::InsertNode(
    Node* insert_node) {
  iterator it_result;
  if (root_ == nullptr) {
    root_ = insert_node;
    root_->right_ = after_last_;
    after_last_->parent_ = root_;
    iterator it(root_);
    it_result = it;
  } else {
    Node* tmp_current = root_;
    // находим ноду, от кот. делаем потомка
    while ((insert_node->data_ < tmp_current->data_ && tmp_current->left_) ||
           (insert_node->data_ >= tmp_current->data_ && tmp_current->right_ &&
            tmp_current->right_ != after_last_)) {
      if (insert_node->data_ < tmp_current->data_)
        tmp_current = tmp_current->left_;
      else
        tmp_current = tmp_current->right_;
    }
    // вставляем потомка
    bool left_step = (insert_node->data_ < tmp_current->data_);
    bool right_step = (insert_node->data_ >= tmp_current->data_);
    if (left_step) {
      tmp_current->left_ = insert_node;
      insert_node->parent_ = tmp_current;
    } else if (right_step) {
      if (tmp_current->right_ == after_last_) {
        insert_node->right_ = after_last_;
        after_last_->parent_ = insert_node;
      }
      tmp_current->right_ = insert_node;
      insert_node->parent_ = tmp_current;
    }
    iterator it(insert_node);
    it_result = it;
  }
  return it_result;
}

template <typename key_type>
void MultiSet<key_type>::merge(MultiSet& other) {
  if (this != &other && other.empty() == false) {
    iterator it_other = other.begin();
    while (it_other != other.end()) {
      this->insert(*it_other);
      iterator it_delete = it_other;
      ++it_other;
      other.erase(it_delete);
    }
  }
}

template <typename key_type>
typename MultiSet<key_type>::size_type MultiSet<key_type>::count(
    const_reference key) {
  size_type result = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) ++result;
  }
  return result;
}

template <typename key_type>
std::pair<typename MultiSet<key_type>::iterator,
          typename MultiSet<key_type>::iterator>
MultiSet<key_type>::equal_range(const_reference key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename key_type>
typename MultiSet<key_type>::iterator MultiSet<key_type>::lower_bound(
    const_reference key) {
  iterator result = end();
  for (auto it = begin(); it != end(); ++it) {
    if (*it >= key) {
      result = it;
      break;
    }
  }
  return result;
}

template <typename key_type>
typename MultiSet<key_type>::iterator MultiSet<key_type>::upper_bound(
    const_reference key) {
  iterator result = end();
  for (auto it = begin(); it != end(); ++it) {
    if (*it > key) {
      result = it;
      break;
    }
  }
  return result;
}

template <typename key_type>
template <class... Args>
typename MultiSet<key_type>::iterator MultiSet<key_type>::emplace(
    Args&&... args) {
  if ((size() + 1) > max_size()) throw std::out_of_range("Limit is exceeded");
  Node* insert_node(new Node(std::forward<Args>(args)...));
  return InsertNode(insert_node);
}

}  // namespace my

#endif  //  MY_MULTISET_H_
