#include <gtest/gtest.h>

#include <set>

#include "../containers/my_containers.h"

TEST(Set_Constructors, default_constructor) {
  my::Set<int> my_set_1;
  std::set<int> orig_set_1;
  ASSERT_TRUE(my_set_1.empty());
  ASSERT_TRUE(orig_set_1.empty());
  ASSERT_EQ(my_set_1.size(), orig_set_1.size());
  ASSERT_EQ(my_set_1.max_size(), orig_set_1.max_size());

  my::Set<std::string> my_set_2;
  std::set<std::string> orig_set_2;
  ASSERT_TRUE(my_set_2.empty());
  ASSERT_TRUE(orig_set_2.empty());
  ASSERT_EQ(my_set_2.size(), orig_set_2.size());
  ASSERT_EQ(my_set_2.max_size(), orig_set_2.max_size());

  my::Set<double> my_set_3;
  std::set<double> orig_set_3;
  ASSERT_TRUE(my_set_3.empty());
  ASSERT_TRUE(orig_set_3.empty());
  ASSERT_EQ(my_set_3.size(), orig_set_3.size());
  ASSERT_EQ(my_set_3.max_size(), orig_set_3.max_size());

  my::Set<char> my_set_4;
  std::set<char> orig_set_4;
  ASSERT_TRUE(my_set_4.empty());
  ASSERT_TRUE(orig_set_4.empty());
  ASSERT_EQ(my_set_4.size(), orig_set_4.size());
  ASSERT_EQ(my_set_4.max_size(), orig_set_4.max_size());
}

TEST(Set_Constructors, initializer_list_constructor) {
  my::Set<int> my_set_1{5, 3, 7, 6, 4, 0};
  std::set<int> orig_set_1{5, 3, 7, 6, 4, 0};
  ASSERT_FALSE(my_set_1.empty());
  ASSERT_EQ(my_set_1.size(), orig_set_1.size());

  my::Set<std::string> my_set_2{"Elefant", "Fox", "Lion",  "Bear",
                                "Giraffe", "Cat", "Tiger", "Crocodile"};
  std::set<std::string> orig_set_2{"Elefant", "Fox", "Lion",  "Bear",
                                   "Giraffe", "Cat", "Tiger", "Crocodile"};
  ASSERT_FALSE(my_set_2.empty());
  ASSERT_EQ(my_set_2.size(), orig_set_2.size());

  my::Set<double> my_set_3{0.009};
  std::set<double> orig_set_3{0.009};
  ASSERT_FALSE(my_set_3.empty());
  ASSERT_EQ(my_set_3.size(), orig_set_3.size());

  my::Set<char> my_set_4{'a', 'b', 'c', 'd', 'e'};
  std::set<char> orig_set_4{'a', 'b', 'c', 'd', 'e'};
  ASSERT_FALSE(my_set_4.empty());
  ASSERT_EQ(my_set_4.size(), orig_set_4.size());
}

TEST(Set_Constructors, copy_constructor_overload_assignment) {
  my::Set<std::string> my_set_1{"Elefant", "Fox", "Lion",  "Bear",
                                "Giraffe", "Cat", "Tiger", "Crocodile"};
  my::Set<std::string> my_set_1_copy(my_set_1);
  ASSERT_EQ(my_set_1_copy.size(), my_set_1.size());

  my::Set<char> my_set_2{'a', 'b', 'c', 'd', 'e'};
  my::Set<char> my_set_2_copy(my_set_2);
  ASSERT_EQ(my_set_2_copy.size(), my_set_2.size());

  my::Set<double> my_set_3({0.003, 0.005, 0.001, 0.007});
  my::Set<double> my_set_3_copy(my_set_3);
  ASSERT_EQ(my_set_3_copy.size(), my_set_3.size());
  double map_3[4] = {0.001, 0.003, 0.005, 0.007};
  int i = 0;
  for (auto it = my_set_3_copy.begin(); it != my_set_3_copy.end(); ++it) {
    double key = *(my_set_3_copy.find(*it));
    ASSERT_EQ(key, map_3[i]);
    ++i;
  }
}

TEST(Set_Constructors, move_constructor_swap_overload_assignment) {
  my::Set<std::string> my_set_1{"Elefant", "Fox", "Lion",  "Bear",
                                "Giraffe", "Cat", "Tiger", "Crocodile"};
  my::Set<std::string> my_set_1_copy(std::move(my_set_1));
  ASSERT_EQ(my_set_1_copy.size(), 8);
  ASSERT_EQ(my_set_1.size(), 0);

  my::Set<char> my_set_2{'a', 'b', 'c', 'd', 'e'};
  my::Set<char> my_set_2_copy(std::move(my_set_2));
  ASSERT_EQ(my_set_2_copy.size(), 5);
  ASSERT_EQ(my_set_2.size(), 0);

  my::Set<double> my_set_3({0.003, 0.005, 0.001, 0.007});
  my::Set<double> my_set_3_copy(std::move(my_set_3));
  ASSERT_EQ(my_set_3_copy.size(), 4);
  ASSERT_EQ(my_set_3.size(), 0);
  double map_3[4] = {0.001, 0.003, 0.005, 0.007};
  int i = 0;
  for (auto it = my_set_3_copy.cbegin(); it != my_set_3_copy.cend(); ++it) {
    double key = *(my_set_3_copy.find(*it));
    ASSERT_EQ(key, map_3[i]);
    ++i;
  }
}

TEST(Set_Insert, insert_value_type_1) {
  my::Set<std::string> my_set;
  my_set.insert("Fox");
  my_set.insert("Bear");
  my_set.insert("Elefant");
  my_set.insert("Giraffe");
  my_set.insert("Lion");
  auto result_insert = my_set.insert("Lion");
  ASSERT_FALSE(result_insert.second);
  my_set.insert("Cat");
  my_set.insert("Tiger");
  my_set.insert("Crocodile");
  ASSERT_EQ(my_set.size(), 8);
  std::string set_massive[] = {"Bear", "Cat",     "Crocodile", "Elefant",
                               "Fox",  "Giraffe", "Lion",      "Tiger"};
  int i = 0;
  for (auto it = my_set.cbegin(); it != my_set.cend(); ++it) {
    std::string key = *(my_set.find(*it));
    ASSERT_EQ(key, set_massive[i]);
    ++i;
  }
}

TEST(Set_Insert, insert_value_type_2) {
  my::Set<std::string> my_set;
  my_set.insert("Fox");
  my_set.insert("Bear");
  my_set.insert("Elefant");
  my_set.insert("Giraffe");
  my_set.insert("Lion");
  auto result_insert = my_set.insert("Dog");
  ASSERT_TRUE(result_insert.second);
  my_set.insert("Cat");
  my_set.insert("Tiger");
  my_set.insert("Crocodile");
  ASSERT_EQ(my_set.size(), 9);
  std::string set_massive[] = {"Bear",    "Cat",     "Crocodile",
                               "Dog",     "Elefant", "Fox",
                               "Giraffe", "Lion",    "Tiger"};
  int i = 0;
  for (auto it = my_set.cbegin(); it != my_set.cend(); ++it) {
    std::string key = *(my_set.find(*it));
    ASSERT_EQ(key, set_massive[i]);
    ++i;
  }
}

TEST(Set_Insert, bonus_emplace) {
  struct MyType {
    int a_;
    int b_;
    double c_;
    MyType() : a_(0), b_(0), c_(0) {}
    MyType(int a, int b, double c) : a_(a), b_(b), c_(c) {}
    bool operator<(const MyType& other) const { return (a_ < other.a_); }
    bool operator<=(const MyType& other) const { return (a_ <= other.a_); }
    bool operator>(const MyType& other) const { return (a_ > other.a_); }
    bool operator>=(const MyType& other) const { return (a_ >= other.a_); }
    bool operator==(const MyType& other) const { return (a_ == other.a_); }
  };
  my::Set<MyType> my_set;
  my_set.emplace(1, 2, 0.1);
  my_set.emplace(3, 4, 0.2);
  my_set.emplace(2, 0, 0.3);

  std::set<MyType> orig_set;
  orig_set.emplace(1, 2, 0.1);
  orig_set.emplace(3, 4, 0.2);
  orig_set.emplace(2, 0, 0.3);

  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  while (my_it != my_set.end() && orig_it != orig_set.end()) {
    ASSERT_EQ((*my_it).a_, (*orig_it).a_);
    ASSERT_EQ((*my_it).b_, (*orig_it).b_);
    ASSERT_DOUBLE_EQ((*my_it).c_, (*orig_it).c_);
    ++my_it;
    ++orig_it;
  }
}

TEST(Set_Erase, erase_test) {
  my::Set<std::string> furniture{"Chair",    "Bed",    "Wardrobe", "Armchair",
                                 "Cupboard", "Desk",   "Table",    "Sofa",
                                 "Couch",    "Bureau", "Stool",    "Dresser"};
  furniture.erase(furniture.find("Bureau"));
  ASSERT_FALSE(furniture.contains("Bureau"));
  furniture.erase(furniture.find("Cupboard"));
  ASSERT_FALSE(furniture.contains("Cupboard"));
  furniture.erase(furniture.find("Table"));
  ASSERT_FALSE(furniture.contains("Table"));
  furniture.erase(furniture.find("Wardrobe"));
  ASSERT_FALSE(furniture.contains("Wardrobe"));
  furniture.erase(furniture.find("Chair"));
  ASSERT_FALSE(furniture.contains("Chair"));
  ASSERT_EQ(furniture.size(), 7);

  my::Set<int> figures{5, 3, 7, 1, 2, 6, 10, 8, 9, 4};
  figures.erase(figures.find(1));
  ASSERT_FALSE(figures.contains(1));
  figures.erase(figures.find(2));
  ASSERT_FALSE(figures.contains(2));
  figures.erase(figures.find(7));
  ASSERT_FALSE(figures.contains(7));
  figures.erase(figures.find(10));
  ASSERT_FALSE(figures.contains(10));
  figures.erase(figures.find(5));
  ASSERT_FALSE(figures.contains(5));
  ASSERT_EQ(figures.size(), 5);
}

TEST(Set_Merge, merge_test) {
  my::Set<std::string> animals{"Elefant", "Fox",      "Bear",  "Lion",
                               "Giraffe", "Cat",      "Tiger", "Snail",
                               "Spider",  "Crocodile"};
  my::Set<std::string> fruits{"Cherry", "Orange", "Fox",    "Grapes",
                              "Peach",  "Pear",   "Banana", "Ananas"};
  my::Set<std::string> set_merge;

  set_merge.merge(animals);
  ASSERT_EQ(set_merge.size(), 10);
  ASSERT_EQ(animals.size(), 0);
  set_merge.merge(fruits);
  ASSERT_EQ(set_merge.size(), 17);
  ASSERT_EQ(fruits.size(), 1);

  std::string merge_massive[] = {
      "Ananas",  "Banana", "Bear",    "Cat",    "Cherry", "Crocodile",
      "Elefant", "Fox",    "Giraffe", "Grapes", "Lion",   "Orange",
      "Peach",   "Pear",   "Snail",   "Spider", "Tiger"};
  int i = 0;
  for (auto it = set_merge.cbegin(); it != set_merge.cend(); ++it) {
    std::string key = *it;
    ASSERT_EQ(key, merge_massive[i]);
    ++i;
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
