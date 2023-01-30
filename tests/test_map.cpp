#include <gtest/gtest.h>

#include <map>

#include "../containers/my_containers.h"

TEST(Map_Constructors, default_constructor) {
  my::Map<int, int> my_map_1;
  std::map<int, int> orig_map_1;
  ASSERT_TRUE(my_map_1.empty());
  ASSERT_TRUE(orig_map_1.empty());
  ASSERT_EQ(my_map_1.size(), orig_map_1.size());
  ASSERT_EQ(my_map_1.max_size(), orig_map_1.max_size());

  my::Map<int, std::string> my_map_2;
  std::map<int, std::string> orig_map_2;
  ASSERT_TRUE(my_map_2.empty());
  ASSERT_TRUE(orig_map_2.empty());
  ASSERT_EQ(my_map_2.size(), orig_map_2.size());
  ASSERT_EQ(my_map_2.max_size(), orig_map_2.max_size());

  my::Map<size_t, double> my_map_3;
  std::map<size_t, double> orig_map_3;
  ASSERT_TRUE(my_map_3.empty());
  ASSERT_TRUE(orig_map_3.empty());
  ASSERT_EQ(my_map_3.size(), orig_map_3.size());
  ASSERT_EQ(my_map_3.max_size(), orig_map_3.max_size());

  my::Map<char, double> my_map_4;
  std::map<char, double> orig_map_4;
  ASSERT_TRUE(my_map_4.empty());
  ASSERT_TRUE(orig_map_4.empty());
  ASSERT_EQ(my_map_4.size(), orig_map_4.size());
  ASSERT_EQ(my_map_4.max_size(), orig_map_4.max_size());

  my::Map<std::string, std::string> my_map_5;
  std::map<std::string, std::string> orig_map_5;
  ASSERT_TRUE(my_map_5.empty());
  ASSERT_TRUE(orig_map_5.empty());
  ASSERT_EQ(my_map_5.size(), orig_map_5.size());
  ASSERT_EQ(my_map_5.max_size(), orig_map_5.max_size());
}
TEST(Map_Constructors, initializer_list_constructor) {
  my::Map<int, int> my_map_1{std::make_pair(5, 0), std::make_pair(3, 1),
                             std::make_pair(7, 1), std::make_pair(6, 0),
                             std::make_pair(4, 1), std::make_pair(0, 0)};
  std::map<int, int> orig_map_1{std::make_pair(5, 0), std::make_pair(3, 1),
                                std::make_pair(7, 1), std::make_pair(6, 0),
                                std::make_pair(4, 1), std::make_pair(0, 0)};
  ASSERT_FALSE(my_map_1.empty());
  ASSERT_EQ(my_map_1.size(), orig_map_1.size());
  ASSERT_EQ(my_map_1.at(5), orig_map_1.at(5));

  my::Map<int, std::string> my_map_2{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile")};
  std::map<int, std::string> orig_map_2{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile")};
  ASSERT_FALSE(my_map_2.empty());
  ASSERT_EQ(my_map_2.size(), orig_map_2.size());
  ASSERT_EQ(my_map_2.at(2), orig_map_2.at(2));

  my::Map<size_t, double> my_map_3({std::make_pair(1, 0.009)});
  std::map<size_t, double> orig_map_3({std::make_pair(1, 0.009)});
  ASSERT_FALSE(my_map_3.empty());
  ASSERT_EQ(my_map_3.size(), orig_map_3.size());
  ASSERT_DOUBLE_EQ(my_map_3.at(1), orig_map_3.at(1));

  my::Map<char, double> my_map_4(
      {std::make_pair('c', 0.001), std::make_pair('b', 0.003),
       std::make_pair('d', 0.005), std::make_pair('e', 0.007)});
  std::map<char, double> orig_map_4(
      {std::make_pair('c', 0.001), std::make_pair('b', 0.003),
       std::make_pair('d', 0.005), std::make_pair('e', 0.007)});
  ASSERT_FALSE(my_map_4.empty());
  ASSERT_EQ(my_map_4.size(), orig_map_4.size());
  ASSERT_DOUBLE_EQ(my_map_4.at('b'), orig_map_4.at('b'));

  my::Map<std::string, std::string> my_map_5{
      std::make_pair("Warbrobe", "Black"), std::make_pair("Bed", "White"),
      std::make_pair("Table", "Yellow"), std::make_pair("Chair", "Red")};
  std::map<std::string, std::string> orig_map_5{
      std::make_pair("Warbrobe", "Black"), std::make_pair("Bed", "White"),
      std::make_pair("Table", "Yellow"), std::make_pair("Chair", "Red")};
  ASSERT_FALSE(my_map_5.empty());
  ASSERT_EQ(my_map_5.size(), orig_map_5.size());
  ASSERT_EQ(my_map_5.at("Table"), orig_map_5.at("Table"));
}

TEST(Map_Constructors, copy_constructor_overload_assignment) {
  my::Map<int, std::string> my_map_2{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile")};
  my::Map<int, std::string> my_map_2_copy(my_map_2);
  ASSERT_EQ(my_map_2_copy.size(), my_map_2.size());
  for (auto it = my_map_2_copy.cbegin(); it != my_map_2_copy.cend(); ++it) {
    int key = (*it).first;
    ASSERT_EQ(my_map_2_copy.at(key), my_map_2.at(key));
  }

  my::Map<char, double> my_map_4(
      {std::make_pair('c', 0.001), std::make_pair('b', 0.003),
       std::make_pair('d', 0.005), std::make_pair('e', 0.007)});
  my::Map<char, double> my_map_4_copy(my_map_4);
  ASSERT_EQ(my_map_4_copy.size(), my_map_4.size());
  for (auto it = my_map_4_copy.cbegin(); it != my_map_4_copy.cend(); ++it) {
    int key = (*it).first;
    ASSERT_DOUBLE_EQ(my_map_4_copy.at(key), my_map_4.at(key));
  }
}

TEST(Map_Constructors, move_constructor_swap_overload_assignment) {
  my::Map<int, std::string> my_map_2{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile")};
  my::Map<int, std::string> my_map_2_copy(std::move(my_map_2));
  ASSERT_EQ(my_map_2_copy.size(), 8);
  ASSERT_EQ(my_map_2.size(), 0);
  std::string map_2[8] = {"Bear", "Giraffe", "Fox",       "Elefant",
                          "Cat",  "Lion",    "Crocodile", "Tiger"};
  int i = 0;
  for (auto it = my_map_2_copy.cbegin(); it != my_map_2_copy.cend(); ++it) {
    int key = (*it).first;
    ASSERT_EQ(my_map_2_copy.at(key), map_2[i]);
    ++i;
  }

  my::Map<char, double> my_map_4(
      {std::make_pair('c', 0.001), std::make_pair('b', 0.003),
       std::make_pair('d', 0.005), std::make_pair('e', 0.007)});
  my::Map<char, double> my_map_4_copy(std::move(my_map_4));
  ASSERT_EQ(my_map_4_copy.size(), 4);
  ASSERT_EQ(my_map_4.size(), 0);
  double map_4[4] = {0.003, 0.001, 0.005, 0.007};
  i = 0;
  for (auto it = my_map_4_copy.cbegin(); it != my_map_4_copy.cend(); ++it) {
    int key = (*it).first;
    ASSERT_DOUBLE_EQ(my_map_4_copy.at(key), map_4[i]);
    ++i;
  }
}

TEST(Map_Insert, insert_value_type) {
  my::Map<int, std::string> my_map;
  my_map.insert(std::pair<int, std::string>(3, "Fox"));
  my_map.insert(std::pair<int, std::string>(1, "Bear"));
  my_map.insert(std::pair<int, std::string>(5, "Elefant"));
  my_map.insert(std::pair<int, std::string>(2, "Giraffe"));
  my_map.insert(std::pair<int, std::string>(7, "Leo"));
  my_map.insert(std::pair<int, std::string>(2, "Dog"));
  auto result_insert = my_map.insert(std::pair<int, std::string>(6, "Cat"));
  ASSERT_TRUE(result_insert.second);
  ASSERT_EQ((*(result_insert.first)).first, 6);
  ASSERT_EQ((*(result_insert.first)).second, "Cat");
  ASSERT_EQ(my_map.size(), 6);
  std::pair<int, std::string> map_massive[6] = {{1, "Bear"}, {2, "Giraffe"},
                                                {3, "Fox"},  {5, "Elefant"},
                                                {6, "Cat"},  {7, "Leo"}};
  int i = 0;
  for (auto it = my_map.cbegin(); it != my_map.cend(); ++it) {
    int key = (*it).first;
    std::string mapped = (*it).second;
    ASSERT_EQ(key, map_massive[i].first);
    ASSERT_EQ(mapped, map_massive[i].second);
    ++i;
  }
}

TEST(Map_Insert, insert_initialized_list) {
  my::Map<std::string, size_t> my_map;
  my_map.insert({{"Chair", 1000},
                 {"Bed", 2000},
                 {"Wardrobe", 4000},
                 {"Armchair", 1500},
                 {"Cupboard", 5000},
                 {"Desk", 3000},
                 {"Table", 4900},
                 {"Sofa", 6700},
                 {"Couch", 1300},
                 {"Bureau", 2500},
                 {"Stool", 4600},
                 {"Dresser", 8900}});
  ASSERT_EQ(my_map.size(), 12);
  std::pair<std::string, size_t> map_massive[] = {
      {"Armchair", 1500}, {"Bed", 2000},     {"Bureau", 2500},
      {"Chair", 1000},    {"Couch", 1300},   {"Cupboard", 5000},
      {"Desk", 3000},     {"Dresser", 8900}, {"Sofa", 6700},
      {"Stool", 4600},    {"Table", 4900},   {"Wardrobe", 4000}};
  int i = 0;
  for (auto it = my_map.cbegin(); it != my_map.cend(); ++it) {
    std::string key = (*it).first;
    size_t mapped = (*it).second;
    ASSERT_EQ(key, map_massive[i].first);
    ASSERT_EQ(mapped, map_massive[i].second);
    ++i;
  }
}

TEST(Map_Insert, insert_key_mapped) {
  my::Map<int, std::string> my_map;
  my_map.insert(3, "Fox");
  my_map.insert(1, "Bear");
  my_map.insert(5, "Elefant");
  my_map.insert(2, "Giraffe");
  my_map.insert(7, "Leo");
  auto result_insert = my_map.insert(2, "Dog");
  my_map.insert(6, "Cat");
  my_map.insert(10, "Tiger");
  my_map.insert(8, "Crocodile");
  ASSERT_FALSE(result_insert.second);
  ASSERT_EQ((*(result_insert.first)).first, 2);
  ASSERT_EQ((*(result_insert.first)).second, "Giraffe");
  ASSERT_EQ(my_map.size(), 8);
  std::pair<int, std::string> map_massive[] = {
      {1, "Bear"}, {2, "Giraffe"}, {3, "Fox"},       {5, "Elefant"},
      {6, "Cat"},  {7, "Leo"},     {8, "Crocodile"}, {10, "Tiger"}};
  int i = 0;
  for (auto it = my_map.cbegin(); it != my_map.cend(); ++it) {
    int key = (*it).first;
    std::string mapped = (*it).second;
    ASSERT_EQ(key, map_massive[i].first);
    ASSERT_EQ(mapped, map_massive[i].second);
    ++i;
  }
}

TEST(Map_Insert, insert_and_assign) {
  my::Map<int, std::string> my_map;
  my_map.insert_or_assign(3, "Fox");
  my_map.insert_or_assign(1, "Bear");
  my_map.insert_or_assign(5, "Elefant");
  my_map.insert_or_assign(2, "Giraffe");
  my_map.insert_or_assign(7, "Leo");
  auto result_insert = my_map.insert_or_assign(2, "Dog");
  my_map.insert_or_assign(6, "Cat");
  my_map.insert_or_assign(10, "Tiger");
  my_map.insert_or_assign(8, "Crocodile");
  ASSERT_FALSE(result_insert.second);
  ASSERT_EQ((*(result_insert.first)).first, 2);
  ASSERT_EQ((*(result_insert.first)).second, "Dog");
  ASSERT_EQ(my_map.size(), 8);
  std::pair<int, std::string> map_massive[] = {
      {1, "Bear"}, {2, "Dog"}, {3, "Fox"},       {5, "Elefant"},
      {6, "Cat"},  {7, "Leo"}, {8, "Crocodile"}, {10, "Tiger"}};
  int i = 0;
  for (auto it = my_map.cbegin(); it != my_map.cend(); ++it) {
    int key = (*it).first;
    std::string mapped = (*it).second;
    ASSERT_EQ(key, map_massive[i].first);
    ASSERT_EQ(mapped, map_massive[i].second);
    ++i;
  }
}

TEST(Map_Insert, overload_square_bracket_contains) {
  my::Map<int, std::string> my_map{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile")};
  ASSERT_EQ(my_map[5], "Elefant");
  ASSERT_EQ(my_map[3], "Fox");
  ASSERT_EQ(my_map[7], "Lion");
  ASSERT_EQ(my_map[1], "Bear");
  ASSERT_EQ(my_map[2], "Giraffe");
  ASSERT_EQ(my_map[6], "Cat");
  ASSERT_EQ(my_map[10], "Tiger");
  ASSERT_EQ(my_map[8], "Crocodile");
  my_map[9] = "Snail";
  my_map[4] = "Spider";
  ASSERT_EQ(my_map[9], "Snail");
  ASSERT_EQ(my_map[4], "Spider");
  ASSERT_EQ(my_map.size(), 10);
}

TEST(Map_Insert, bonus_emplace) {
  my::Map<int, std::string> my_map{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"), std::make_pair(1, "Bear")};
  ASSERT_EQ(my_map.size(), 4);
  my_map.emplace(std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
                 std::make_pair(10, "Tiger"), std::make_pair(8, "Crocodile"));
  ASSERT_EQ(my_map.size(), 8);
  auto it_begin = my_map.begin();
  ASSERT_EQ((*it_begin).first, 1);
  ASSERT_EQ((*it_begin).second, "Bear");
  auto it_last = my_map.end();
  --it_last;
  ASSERT_EQ((*it_last).first, 10);
  ASSERT_EQ((*it_last).second, "Tiger");

  my_map.emplace(std::make_pair(9, "Snail"), std::make_pair(4, "Spider"),
                 std::make_pair(2, "Dog"));
  ASSERT_EQ(my_map.size(), 10);
}

TEST(Map_Erase, erase_test) {
  my::Map<std::string, size_t> furniture{
      {"Chair", 1000},    {"Bed", 2000},      {"Wardrobe", 4000},
      {"Armchair", 1500}, {"Cupboard", 5000}, {"Desk", 3000},
      {"Table", 4900},    {"Sofa", 6700},     {"Couch", 1300},
      {"Bureau", 2500},   {"Stool", 4600},    {"Dresser", 8900}};
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

  my::Map<int, std::string> animals{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile"),
      std::make_pair(9, "Snail"),   std::make_pair(4, "Spider")};
  animals.erase(animals.find(1));
  ASSERT_FALSE(animals.contains(1));
  animals.erase(animals.find(2));
  ASSERT_FALSE(animals.contains(2));
  animals.erase(animals.find(7));
  ASSERT_FALSE(animals.contains(7));
  animals.erase(animals.find(10));
  ASSERT_FALSE(animals.contains(10));
  animals.erase(animals.find(5));
  ASSERT_FALSE(animals.contains(5));
  ASSERT_EQ(animals.size(), 5);
}

TEST(Map_Merge, merge_test) {
  my::Map<int, std::string> animals{
      std::make_pair(5, "Elefant"), std::make_pair(3, "Fox"),
      std::make_pair(7, "Lion"),    std::make_pair(1, "Bear"),
      std::make_pair(2, "Giraffe"), std::make_pair(6, "Cat"),
      std::make_pair(10, "Tiger"),  std::make_pair(8, "Crocodile"),
      std::make_pair(9, "Snail"),   std::make_pair(4, "Spider")};

  my::Map<int, std::string> fruits{
      std::make_pair(5, "Cherry"), std::make_pair(13, "Orange"),
      std::make_pair(7, "Grapes"), std::make_pair(1, "Peach"),
      std::make_pair(2, "Pear"),   std::make_pair(16, "Ananas"),
      std::make_pair(11, "Banana")};
  my::Map<int, std::string> map_merge;
  map_merge.merge(animals);
  ASSERT_EQ(map_merge.size(), 10);
  ASSERT_EQ(animals.size(), 0);

  map_merge.merge(fruits);
  ASSERT_EQ(map_merge.size(), 13);
  ASSERT_EQ(fruits.size(), 4);

  std::pair<int, std::string> merge_massive[] = {
      {1, "Bear"},    {2, "Giraffe"}, {3, "Fox"},     {4, "Spider"},
      {5, "Elefant"}, {6, "Cat"},     {7, "Lion"},    {8, "Crocodile"},
      {9, "Snail"},   {10, "Tiger"},  {11, "Banana"}, {13, "Orange"},
      {16, "Ananas"}};
  int i = 0;
  for (auto it = map_merge.cbegin(); it != map_merge.cend(); ++it) {
    int key = (*it).first;
    std::string mapped = (*it).second;
    ASSERT_EQ(key, merge_massive[i].first);
    ASSERT_EQ(mapped, merge_massive[i].second);
    ++i;
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
