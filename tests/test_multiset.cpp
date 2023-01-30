#include <gtest/gtest.h>

#include <set>

#include "../containers/my_containers.h"

TEST(Multiset_Constructors, default_constructor) {
  my::MultiSet<int> my_1;
  std::multiset<int> orig_1;
  ASSERT_TRUE(my_1.empty());
  ASSERT_TRUE(orig_1.empty());
  ASSERT_EQ(my_1.size(), orig_1.size());
  ASSERT_EQ(my_1.max_size(), orig_1.max_size());

  my::MultiSet<std::string> my_2;
  std::multiset<std::string> orig_2;
  ASSERT_TRUE(my_2.empty());
  ASSERT_TRUE(orig_2.empty());
  ASSERT_EQ(my_2.size(), orig_2.size());
  ASSERT_EQ(my_2.max_size(), orig_2.max_size());

  my::MultiSet<double> my_3;
  std::multiset<double> orig_3;
  ASSERT_TRUE(my_3.empty());
  ASSERT_TRUE(orig_3.empty());
  ASSERT_EQ(my_3.size(), orig_3.size());
  ASSERT_EQ(my_3.max_size(), orig_3.max_size());

  my::MultiSet<char> my_4;
  std::multiset<char> orig_4;
  ASSERT_TRUE(my_4.empty());
  ASSERT_TRUE(orig_4.empty());
  ASSERT_EQ(my_4.size(), orig_4.size());
  ASSERT_EQ(my_4.max_size(), orig_4.max_size());
}

TEST(Multiset_Constructors, initializer_list_constructor) {
  my::MultiSet<int> my_1{5, 3, 0, 3, 7, 0, 6, 4, 7, 0};
  std::multiset<int> orig_1{5, 3, 0, 3, 7, 0, 6, 4, 7, 0};
  ASSERT_FALSE(my_1.empty());
  ASSERT_EQ(my_1.size(), orig_1.size());

  my::MultiSet<std::string> my_2{"Elefant", "Fox", "Lion",  "Bear",
                                 "Giraffe", "Cat", "Tiger", "Crocodile",
                                 "Giraffe", "Cat", "Tiger", "Crocodile"};
  std::multiset<std::string> orig_2{"Elefant", "Fox", "Lion",  "Bear",
                                    "Giraffe", "Cat", "Tiger", "Crocodile",
                                    "Giraffe", "Cat", "Tiger", "Crocodile"};
  ASSERT_FALSE(my_2.empty());
  ASSERT_EQ(my_2.size(), orig_2.size());

  my::MultiSet<double> my_3{0.009, 0.003, 0.1, 0.009};
  std::multiset<double> orig_3{0.009, 0.003, 0.1, 0.009};
  ASSERT_FALSE(my_3.empty());
  ASSERT_EQ(my_3.size(), orig_3.size());

  my::MultiSet<char> my_4{'a', 'b', 'c', 'd', 'e'};
  std::multiset<char> orig_4{'a', 'b', 'c', 'd', 'e'};
  ASSERT_FALSE(my_4.empty());
  ASSERT_EQ(my_4.size(), orig_4.size());
}

TEST(Multiset_Constructors, copy_constructor_overload_assignment) {
  my::MultiSet<std::string> my_1{"Elefant", "Fox", "Lion",  "Bear",
                                 "Giraffe", "Cat", "Tiger", "Crocodile",
                                 "Giraffe", "Cat", "Tiger", "Crocodile"};
  my::MultiSet<std::string> my_1_copy(my_1);
  ASSERT_EQ(my_1_copy.size(), my_1.size());

  my::MultiSet<char> my_2{'a', 'b', 'c', 'd', 'e', 'a', 'b', 'c'};
  my::MultiSet<char> my_2_copy(my_2);
  ASSERT_EQ(my_2_copy.size(), my_2.size());

  my::MultiSet<double> my_3({0.003, 0.005, 0.005, 0.007});
  my::MultiSet<double> my_3_copy(my_3);
  ASSERT_EQ(my_3_copy.size(), my_3.size());
  double map_3[4] = {0.003, 0.005, 0.005, 0.007};
  int i = 0;
  for (auto it = my_3_copy.begin(); it != my_3_copy.end(); ++it) {
    double key = *(my_3_copy.find(*it));
    ASSERT_EQ(key, map_3[i]);
    ++i;
  }
}

TEST(Multiset_Constructors, move_constructor_swap_overload_assignment) {
  my::MultiSet<std::string> my_1{"Elefant", "Fox", "Lion",  "Bear",
                                 "Giraffe", "Cat", "Tiger", "Crocodile",
                                 "Giraffe", "Cat", "Tiger", "Crocodile"};
  my::MultiSet<std::string> my_1_copy(std::move(my_1));
  ASSERT_EQ(my_1_copy.size(), 12);
  ASSERT_EQ(my_1.size(), 0);

  my::MultiSet<char> my_2{'a', 'b', 'c', 'd', 'e', 'a', 'b', 'c'};
  my::MultiSet<char> my_2_copy(std::move(my_2));
  ASSERT_EQ(my_2_copy.size(), 8);
  ASSERT_EQ(my_2.size(), 0);

  my::MultiSet<double> my_3({0.003, 0.005, 0.005, 0.007});
  my::MultiSet<double> my_3_copy(std::move(my_3));
  ASSERT_EQ(my_3_copy.size(), 4);
  ASSERT_EQ(my_3.size(), 0);
  double map_3[4] = {0.003, 0.005, 0.005, 0.007};
  int i = 0;
  for (auto it = my_3_copy.cbegin(); it != my_3_copy.cend(); ++it) {
    double key = *(my_3_copy.find(*it));
    ASSERT_EQ(key, map_3[i]);
    ++i;
  }
}

TEST(Multiset_Insert, insert_value_type_1) {
  my::MultiSet<std::string> my;
  my.insert("Fox");
  my.insert("Bear");
  my.insert("Elefant");
  my.insert("Giraffe");
  my.insert("Lion");
  auto result_insert = my.insert("Lion");
  ASSERT_EQ(*result_insert, "Lion");
  my.insert("Cat");
  my.insert("Tiger");
  my.insert("Crocodile");
  ASSERT_EQ(my.size(), 9);
  std::string set_massive[] = {"Bear",    "Cat",  "Crocodile", "Elefant", "Fox",
                               "Giraffe", "Lion", "Lion",      "Tiger"};
  int i = 0;
  for (auto it = my.cbegin(); it != my.cend(); ++it) {
    std::string key = *(my.find(*it));
    ASSERT_EQ(key, set_massive[i]);
    ++i;
  }
}

TEST(Multiset_Insert, insert_value_type_2) {
  my::MultiSet<std::string> my;
  my.insert("Fox");
  my.insert("Bear");
  my.insert("Elefant");
  my.insert("Giraffe");
  my.insert("Lion");
  auto result_insert = my.insert("Dog");
  ASSERT_EQ(*result_insert, "Dog");
  my.insert("Cat");
  my.insert("Tiger");
  my.insert("Crocodile");
  ASSERT_EQ(my.size(), 9);
  std::string set_massive[] = {"Bear",    "Cat",     "Crocodile",
                               "Dog",     "Elefant", "Fox",
                               "Giraffe", "Lion",    "Tiger"};
  int i = 0;
  for (auto it = my.cbegin(); it != my.cend(); ++it) {
    std::string key = *(my.find(*it));
    ASSERT_EQ(key, set_massive[i]);
    ++i;
  }
}

TEST(Multiset_Insert, bonus_emplace) {
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
  my::MultiSet<MyType> my;
  my.emplace(1, 2, 0.1);
  my.emplace(3, 4, 0.2);
  my.emplace(2, 0, 0.3);
  my.emplace(3, 4, 0.2);
  my.emplace(1, 2, 0.1);

  std::multiset<MyType> orig;
  orig.emplace(1, 2, 0.1);
  orig.emplace(3, 4, 0.2);
  orig.emplace(2, 0, 0.3);
  orig.emplace(3, 4, 0.2);
  orig.emplace(1, 2, 0.1);

  auto my_it = my.begin();
  auto orig_it = orig.begin();
  while (my_it != my.end() && orig_it != orig.end()) {
    ASSERT_EQ((*my_it).a_, (*orig_it).a_);
    ASSERT_EQ((*my_it).b_, (*orig_it).b_);
    ASSERT_DOUBLE_EQ((*my_it).c_, (*orig_it).c_);
    ++my_it;
    ++orig_it;
  }

  ASSERT_EQ(my.size(), orig.size());
}

TEST(Multiset_Erase, erase_test_count) {
  my::MultiSet<std::string> furniture{
      "Chair",  "Bed",    "Cupboard", "Wardrobe", "Armchair", "Cupboard",
      "Bureau", "Desk",   "Table",    "Cupboard", "Sofa",     "Couch",
      "Chair",  "Bureau", "Table",    "Stool",    "Dresser",  "Table"};
  ASSERT_EQ(furniture.count("Bureau"), 2);
  furniture.erase(furniture.find("Bureau"));
  ASSERT_EQ(furniture.count("Bureau"), 1);
  furniture.erase(furniture.find("Bureau"));
  ASSERT_FALSE(furniture.contains("Bureau"));

  ASSERT_EQ(furniture.count("Cupboard"), 3);
  furniture.erase(furniture.find("Cupboard"));
  ASSERT_TRUE(furniture.contains("Cupboard"));

  ASSERT_EQ(furniture.count("Table"), 3);
  furniture.erase(furniture.find("Table"));
  ASSERT_TRUE(furniture.contains("Table"));

  ASSERT_EQ(furniture.count("Wardrobe"), 1);
  furniture.erase(furniture.find("Wardrobe"));
  ASSERT_FALSE(furniture.contains("Wardrobe"));

  ASSERT_EQ(furniture.count("Chair"), 2);
  furniture.erase(furniture.find("Chair"));
  ASSERT_EQ(furniture.count("Chair"), 1);
  furniture.erase(furniture.find("Chair"));
  ASSERT_FALSE(furniture.contains("Chair"));
  ASSERT_EQ(furniture.size(), 11);

  my::MultiSet<int> figures{5, 3, 7, 1, 3, 3, 2, 6, 2, 2, 2, 10, 8, 9, 9, 9, 4};
  ASSERT_EQ(figures.count(1), 1);
  figures.erase(figures.find(1));
  ASSERT_FALSE(figures.contains(1));

  ASSERT_EQ(figures.count(2), 4);
  figures.erase(figures.find(2));
  ASSERT_TRUE(figures.contains(2));

  ASSERT_EQ(figures.count(7), 1);
  figures.erase(figures.find(7));
  ASSERT_FALSE(figures.contains(7));

  ASSERT_EQ(figures.count(10), 1);
  figures.erase(figures.find(10));
  ASSERT_FALSE(figures.contains(10));

  ASSERT_EQ(figures.count(9), 3);
  figures.erase(figures.find(9));
  ASSERT_TRUE(figures.contains(9));

  ASSERT_EQ(figures.size(), 12);
}

TEST(Multiset_Merge, merge_test) {
  my::MultiSet<std::string> animals{"Elefant", "Lion", "Fox",
                                    "Lion",    "Bear", "Lion"};
  my::MultiSet<std::string> fruits{"Cherry", "Ananas", "Orange", "Ananas",
                                   "Bear",   "Grapes", "Ananas", "Bear"};
  my::MultiSet<std::string> map_merge;

  map_merge.merge(animals);
  ASSERT_EQ(map_merge.size(), 6);
  ASSERT_EQ(animals.size(), 0);
  map_merge.merge(fruits);
  ASSERT_EQ(map_merge.size(), 14);
  ASSERT_EQ(fruits.size(), 0);

  std::string merge_massive[] = {
      "Ananas",  "Ananas", "Ananas", "Bear", "Bear", "Bear", "Cherry",
      "Elefant", "Fox",    "Grapes", "Lion", "Lion", "Lion", "Orange"};
  int i = 0;
  for (auto it = map_merge.cbegin(); it != map_merge.cend(); ++it) {
    std::string key = *it;
    ASSERT_EQ(key, merge_massive[i]);
    ++i;
  }
}

TEST(Multiset_Equal_Eange, equal_range_test) {
  my::MultiSet<int> my_figures{5, 3, 7,  1, 3, 3, 2, 6, 2,
                               2, 2, 10, 8, 9, 9, 9, 4};
  std::multiset<int> orig_figures{5, 3, 7,  1, 3, 3, 2, 6, 2,
                                  2, 2, 10, 8, 9, 9, 9, 4};
  auto my_result = my_figures.equal_range(3);
  auto orig_result = orig_figures.equal_range(3);
  ASSERT_EQ(*(my_result.first), *(orig_result.first));
  ASSERT_EQ(*(my_result.second), *(orig_result.second));

  my_result = my_figures.equal_range(9);
  orig_result = orig_figures.equal_range(9);
  ASSERT_EQ(*(my_result.first), *(orig_result.first));
  ASSERT_EQ(*(my_result.second), *(orig_result.second));

  my_result = my_figures.equal_range(5);
  orig_result = orig_figures.equal_range(5);
  ASSERT_EQ(*(my_result.first), *(orig_result.first));
  ASSERT_EQ(*(my_result.second), *(orig_result.second));

  my_result = my_figures.equal_range(12);
  ASSERT_TRUE(my_result.first == my_figures.end());
  ASSERT_TRUE(my_result.second == my_figures.end());
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
