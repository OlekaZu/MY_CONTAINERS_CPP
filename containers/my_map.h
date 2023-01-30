#ifndef MY_MAP_H_
#define MY_MAP_H_

#include <iostream>
#include <limits>

using std::cout;
using std::endl;

namespace my {
template <typename Key, typename T>
class Map {
  class Node;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  class MapIterator {
   public:
    MapIterator() : current_node_(nullptr) {}
    explicit MapIterator(Node* ptr_node) : current_node_(ptr_node) {}

    Node* GetCurrentNode() { return current_node_; }
    MapIterator& operator++() {
      if (current_node_->right_ == nullptr && current_node_->parent_) {
        while (current_node_->data_.first > current_node_->parent_->data_.first)
          current_node_ = current_node_->parent_;
        current_node_ = current_node_->parent_;
      } else {
        current_node_ = current_node_->right_;
        while (current_node_->left_) current_node_ = current_node_->left_;
      }
      return *this;
    }
    MapIterator operator++(int) {
      MapIterator tmp(*this);
      ++(*this);
      return tmp;
    }
    MapIterator& operator--() {
      if (current_node_->left_ == nullptr && current_node_->parent_) {
        // если мы стоим на after_last_ноде
        if (current_node_->place_holder_ == true) {
          current_node_ = current_node_->parent_;
        } else {
          while (current_node_->data_.first <
                 current_node_->parent_->data_.first)
            current_node_ = current_node_->parent_;
          current_node_ = current_node_->parent_;
        }
      } else if (current_node_->left_) {
        current_node_ = current_node_->left_;
        while (current_node_->right_) current_node_ = current_node_->right_;
      }
      return *this;
    }
    MapIterator operator--(int) {
      MapIterator tmp(*this);
      --(*this);
      return tmp;
    }
    const_reference operator*() { return current_node_->data_; }

    bool operator==(const MapIterator& other) {
      return this->current_node_ == other.current_node_;
    }

    bool operator!=(const MapIterator& other) {
      return this->current_node_ != other.current_node_;
    }

   private:
    Node* current_node_;
  };

  using iterator = MapIterator;
  using const_iterator = const MapIterator;

  /*------ Constructors & Destructor ------*/
  Map();
  explicit Map(std::initializer_list<value_type> const& items);
  Map(const Map& m);
  Map(Map&& m);
  ~Map();
  Map& operator=(const Map& m);
  Map& operator=(Map&& m);

  /*------ Map Element access ------*/
  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  /*------ Map Iterators ------*/
  iterator begin();
  iterator end();
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  /*------ Map Capacity ------*/
  bool empty();
  size_type size();
  size_type max_size();

  /*------ Map Modifiers ------*/
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void insert(std::initializer_list<value_type> ilist);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  void erase(iterator pos);
  void swap(Map& other);
  void merge(Map& other);

  /*------ Map Lookup ------*/
  bool contains(const key_type& key);

  /*------ Bonus Methods ------*/
  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args);

  /*------ Helping Methods ------*/
  iterator find(const key_type& key);
  void ShowMapSort();

 private:
  class Node {
   public:
    value_type data_;
    Node* left_;
    Node* right_;
    Node* parent_;
    bool place_holder_;
    Node()
        : data_(),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr),
          place_holder_(false) {}
    explicit Node(value_type data)
        : data_(data),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr),
          place_holder_(false) {}
  };

  Node* root_;
  Node* after_last_;

  /*------ Helping Methods ------*/
  void BalanceAfterDelete(Node* deleted_node);
  void ChangeNodes(Node* deleted_node, Node* exchange_node, int depth);
  void PrintNode(Node* tmp_current);
  void Clear(Node* delete_node);
};

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map() : root_(nullptr) {
  after_last_ = new Node;
  after_last_->place_holder_ = true;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(std::initializer_list<value_type> const& items)
    : Map() {
  for (auto element : items) insert(element);
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(const Map& m) : Map() {
  *this = m;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(Map&& m) : Map() {
  *this = std::move(m);
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::~Map() {
  clear();
  delete after_last_;
  after_last_ = nullptr;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>& Map<key_type, mapped_type>::operator=(
    const Map& m) {
  if (this == &m) throw std::out_of_range("Coping the same map is forbidden!");
  clear();
  for (auto it = m.cbegin(); it != m.cend(); ++it) this->insert(*it);
  return *this;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>& Map<key_type, mapped_type>::operator=(Map&& m) {
  swap(m);
  m.clear();
  return *this;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::at(const key_type& key) {
  iterator it_result = find(key);
  if (it_result == end())
    throw std::out_of_range("There is no such key in the map!");
  Node* result = it_result.GetCurrentNode();
  return result->data_.second;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::operator[](const key_type& key) {
  if (contains(key) == false) insert(key, mapped_type());
  iterator it_result = find(key);
  Node* result = it_result.GetCurrentNode();
  return result->data_.second;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::begin() {
  Node* tmp_node = root_;
  while (tmp_node->left_) tmp_node = tmp_node->left_;
  iterator it(tmp_node);
  return it;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::const_iterator
Map<key_type, mapped_type>::cbegin() const noexcept {
  Node* tmp_node = root_;
  while (tmp_node->left_) tmp_node = tmp_node->left_;
  const_iterator it(tmp_node);
  return it;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::end() {
  iterator it(after_last_);
  return it;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::const_iterator
Map<key_type, mapped_type>::cend() const noexcept {
  const_iterator it(after_last_);
  return it;
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::empty() {
  return (root_ == nullptr);
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::size() {
  size_type result = 0;
  if (root_) {
    for (auto it = begin(); it != end(); ++it) ++result;
  }
  return result;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::max_size() {
  size_type max_size =
      (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
  return max_size;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::clear() {
  if (root_) Clear(root_);
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const_reference value) {
  if ((size() + 1) > max_size()) throw std::out_of_range("Limit is exceeded");
  Node* insert_node(new Node(value));
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
    while ((value.first < tmp_current->data_.first && tmp_current->left_) ||
           (value.first > tmp_current->data_.first && tmp_current->right_ &&
            tmp_current->right_ != after_last_)) {
      if (value.first < tmp_current->data_.first)
        tmp_current = tmp_current->left_;
      else
        tmp_current = tmp_current->right_;
    }
    // вставляем потомка
    bool left_step = (value.first < tmp_current->data_.first);
    bool right_step = (value.first > tmp_current->data_.first);
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
    } else {
      iterator it(tmp_current);
      Clear(insert_node);
      return std::pair<iterator, bool>(it, false);
    }
    iterator it(insert_node);
    it_result = it;
  }
  return std::pair<iterator, bool>(it_result, true);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::insert(
    std::initializer_list<value_type> ilist) {
  for (auto& element : ilist) insert(element);
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  return insert(std::make_pair(key, obj));
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  iterator it_found_node = find(key);
  Node* found_node = it_found_node.GetCurrentNode();
  if (found_node == after_last_) return insert(std::make_pair(key, obj));
  found_node->data_.second = obj;
  return std::pair<iterator, bool>(it_found_node, false);
}

template <typename key_type, typename mapped_type>
template <class... Args>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::emplace(Args&&... args) {
  std::vector<std::pair<iterator, bool>> list_of_insertion;
  for (auto& it_args :
       std::initializer_list<std::pair<key_type, mapped_type>>{args...}) {
    auto result_pair = insert(it_args);
    list_of_insertion.push_back(result_pair);
  }
  return list_of_insertion.empty() ? std::make_pair(end(), false)
                                   : list_of_insertion.back();
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::erase(iterator pos) {
  if (pos != end() && root_) {
    Node* deleted_node = pos.GetCurrentNode();
    BalanceAfterDelete(deleted_node);
    delete deleted_node;
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::swap(Map& other) {
  if (this != &other) {
    std::swap(this->root_, other.root_);
    std::swap(this->after_last_, other.after_last_);
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::merge(Map& other) {
  if (this != &other && other.empty() == false) {
    iterator it_other = other.begin();
    while (it_other != other.end()) {
      if (contains((*it_other).first) == false) {
        insert(*it_other);
        iterator it_delete = it_other;
        ++it_other;
        other.erase(it_delete);
      } else {
        ++it_other;
      }
    }
  }
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type& key) {
  bool result = true;
  if (find(key) == end()) result = false;
  return result;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator Map<key_type, mapped_type>::find(
    const key_type& key) {
  iterator result = end();
  if (root_) {
    iterator it_current_node(root_);
    while (key > (*it_current_node).first &&
           it_current_node.GetCurrentNode() != after_last_)
      ++it_current_node;
    while (key < (*it_current_node).first && it_current_node != begin())
      --it_current_node;
    if (key == (*it_current_node).first) result = it_current_node;
  }
  return result;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::BalanceAfterDelete(Node* deleted_node) {
  Node* exchange_node = nullptr;
  int count_depth = 0;
  // нет потомков и это не корень
  if (!deleted_node->left_ && !deleted_node->right_ && deleted_node != root_) {
    if (deleted_node->parent_->left_ == deleted_node)
      deleted_node->parent_->left_ = nullptr;
    else
      deleted_node->parent_->right_ = nullptr;
    // один правый потомок
  } else if (!deleted_node->left_ && deleted_node->right_) {
    exchange_node = deleted_node->right_;
    ChangeNodes(deleted_node, exchange_node, count_depth);
    // один левый потомок
  } else if (deleted_node->left_ && !deleted_node->right_) {
    exchange_node = deleted_node->left_;
    ChangeNodes(deleted_node, exchange_node, count_depth);
    // 2 потомка
  } else if (deleted_node->left_ && deleted_node->right_) {
    exchange_node = deleted_node->right_;
    while (exchange_node->left_) {
      exchange_node = exchange_node->left_;
      ++count_depth;
    }
    // если удаляем последний элемент
    if (deleted_node->right_ == after_last_) {
      iterator new_last(deleted_node);
      --new_last;
      if (deleted_node != root_) {
        deleted_node->parent_->right_ = deleted_node->left_;
        deleted_node->left_->parent_ = deleted_node->parent_;
      }
      exchange_node = new_last.GetCurrentNode();
      exchange_node->right_ = after_last_;
      after_last_->parent_ = exchange_node;
    } else {
      if (count_depth && exchange_node->right_) {
        exchange_node->parent_->left_ = exchange_node->right_;
        exchange_node->right_->parent_ = exchange_node->parent_;
      } else if (count_depth && !exchange_node->right_) {
        exchange_node->parent_->left_ = nullptr;
      }
      ChangeNodes(deleted_node, exchange_node, count_depth);
    }
  }
  if (deleted_node == root_) {
    if (exchange_node) exchange_node->parent_ = nullptr;
    root_ = exchange_node;
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::ChangeNodes(Node* deleted_node,
                                             Node* exchange_node, int depth) {
  if (deleted_node != root_) {
    bool parent_from_left = (deleted_node->parent_->left_ == deleted_node);
    if (parent_from_left) {
      deleted_node->parent_->left_ = exchange_node;
      exchange_node->parent_ = deleted_node->parent_;
    } else {
      deleted_node->parent_->right_ = exchange_node;
      exchange_node->parent_ = deleted_node->parent_;
    }
  }
  // если 2 потомка и count_depth !=0
  if (deleted_node->left_ && deleted_node->right_) {
    deleted_node->left_->parent_ = exchange_node;
    exchange_node->left_ = deleted_node->left_;
    if (depth) {
      deleted_node->right_->parent_ = exchange_node;
      exchange_node->right_ = deleted_node->right_;
    }
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::ShowMapSort() {
  cout << "Input of MY Map:" << endl;
  Node* tmp_current = root_;
  PrintNode(tmp_current);
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::PrintNode(Node* tmp_current) {
  if (tmp_current && tmp_current != after_last_) {
    PrintNode(tmp_current->left_);
    cout << "key: " << tmp_current->data_.first
         << " -- value: " << tmp_current->data_.second << endl;
    PrintNode(tmp_current->right_);
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::Clear(Node* delete_node) {
  if (delete_node->left_) Clear(delete_node->left_);
  if (delete_node->right_) Clear(delete_node->right_);
  if (delete_node != after_last_) delete delete_node;
}

}  // namespace my

#endif  //  MY_MAP_H_
