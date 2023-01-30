#include <gtest/gtest.h>

#include <list>

#include "../containers/my_containers.h"

TEST(List_Constructors, default_constructor) {
  my::List<int> my_list_int;
  ASSERT_TRUE(my_list_int.empty());
  ASSERT_EQ(my_list_int.size(), 0);
  ASSERT_EQ(my_list_int.max_size(), 384307168202282325);

  my::List<size_t> my_list_size_t;
  ASSERT_TRUE(my_list_size_t.empty());
  ASSERT_EQ(my_list_size_t.size(), 0);
  ASSERT_EQ(my_list_size_t.max_size(), 384307168202282325);

  my::List<double> my_list_double;
  ASSERT_TRUE(my_list_double.empty());
  ASSERT_EQ(my_list_double.size(), 0);
  ASSERT_EQ(my_list_double.max_size(), 384307168202282325);

  my::List<char> my_list_char;
  ASSERT_TRUE(my_list_char.empty());
  ASSERT_EQ(my_list_char.size(), 0);
  ASSERT_EQ(my_list_char.max_size(), 384307168202282325);

  my::List<std::string> my_list_string;
  ASSERT_TRUE(my_list_string.empty());
  ASSERT_EQ(my_list_string.size(), 0);
  ASSERT_EQ(my_list_string.max_size(), 192153584101141162);
}

TEST(List_Constructors, parameterized_constructor) {
  my::List<int> my_list_int(3);
  ASSERT_FALSE(my_list_int.empty());
  ASSERT_EQ(my_list_int.size(), 3);
  ASSERT_EQ(my_list_int.max_size(), 384307168202282325);

  my::List<size_t> my_list_size_t(100);
  ASSERT_FALSE(my_list_size_t.empty());
  ASSERT_EQ(my_list_size_t.size(), 100);
  ASSERT_EQ(my_list_size_t.max_size(), 384307168202282325);

  my::List<double> my_list_double(78);
  ASSERT_FALSE(my_list_double.empty());
  ASSERT_EQ(my_list_double.size(), 78);
  ASSERT_EQ(my_list_double.max_size(), 384307168202282325);

  my::List<char> my_list_char(0);
  ASSERT_TRUE(my_list_char.empty());
  ASSERT_EQ(my_list_char.size(), 0);
  ASSERT_EQ(my_list_char.max_size(), 384307168202282325);

  my::List<std::string> my_list_string(205);
  ASSERT_FALSE(my_list_string.empty());
  ASSERT_EQ(my_list_string.size(), 205);
  ASSERT_EQ(my_list_string.max_size(), 192153584101141162);
}

TEST(List_Constructors, initializer_list_constructor) {
  my::List<int> my_list_int{777, -3, 1, 2, 5};
  ASSERT_EQ(my_list_int.size(), 5);
  ASSERT_EQ(my_list_int.front(), 777);
  ASSERT_EQ(my_list_int.back(), 5);

  my::List<std::string> my_list_string{"Hello", "I'm", "Mike"};
  ASSERT_EQ(my_list_string.size(), 3);
  ASSERT_EQ(my_list_string.front(), "Hello");
  ASSERT_EQ(my_list_string.back(), "Mike");
}

TEST(List_Constructors, copy_constructor_iterators) {
  my::List<int> my_list_int{777, -3, 1, 2, 5};
  my::List<int> my_list_int2(my_list_int);
  ASSERT_EQ(my_list_int.size(), 5);
  ASSERT_EQ(my_list_int.front(), 777);
  ASSERT_EQ(my_list_int.back(), 5);
  ASSERT_EQ(my_list_int2.size(), 5);
  ASSERT_EQ(my_list_int2.front(), 777);
  ASSERT_EQ(my_list_int2.back(), 5);

  my::List<std::string> my_list_string{"Hello", "I'm", "Mike"};
  my::List<std::string> my_list_string2(my_list_string);
  ASSERT_EQ(my_list_string.size(), 3);
  ASSERT_EQ(my_list_string.front(), "Hello");
  ASSERT_EQ(my_list_string.back(), "Mike");
  auto it = my_list_string2.begin();
  auto it_end = my_list_string2.end();
  --it_end;
  ASSERT_EQ(*it, "Hello");
  ASSERT_EQ(*it_end, "Mike");
}

TEST(List_Constructors, move_constructor_iterators) {
  my::List<int> my_list_int{777, -3, 1, 2, 5};
  my::List<int> my_list_int2(std::move(my_list_int));
  ASSERT_EQ(my_list_int.size(), 0);
  ASSERT_EQ(my_list_int2.size(), 5);
  ASSERT_EQ(my_list_int2.front(), 777);
  ASSERT_EQ(my_list_int2.back(), 5);

  my::List<std::string> my_list_string{"Hello", "I'm", "Mike"};
  my::List<std::string> my_list_string2(std::move(my_list_string));
  ASSERT_EQ(my_list_string.size(), 0);
  ASSERT_EQ(my_list_string2.size(), 3);
  auto it = my_list_string2.begin();
  auto it_end = my_list_string2.end();
  --it_end;
  ASSERT_EQ(*it, "Hello");
  ASSERT_EQ(*it_end, "Mike");
}

TEST(List_Overload, assignment_operator_swap) {
  my::List<int> my_list_int{777, -3, 1, 2, 5};
  my::List<int> my_list_int2(3);
  my_list_int2 = my_list_int;
  ASSERT_EQ(my_list_int.size(), 5);
  ASSERT_EQ(my_list_int.front(), 777);
  ASSERT_EQ(my_list_int.back(), 5);
  ASSERT_EQ(my_list_int2.size(), 5);
  ASSERT_EQ(my_list_int2.front(), 777);
  ASSERT_EQ(my_list_int2.back(), 5);

  my::List<double> my_list_double{0.5, -3.9, 1.5, 2.3};
  my::List<double> my_list_double2{100.1, 100.2};
  my_list_double2 = my_list_double;
  ASSERT_EQ(my_list_double.size(), 4);
  ASSERT_DOUBLE_EQ(my_list_double.front(), 0.5);
  ASSERT_DOUBLE_EQ(my_list_double.back(), 2.3);
  ASSERT_EQ(my_list_double2.size(), 4);
  ASSERT_DOUBLE_EQ(my_list_double2.front(), 0.5);
  ASSERT_DOUBLE_EQ(my_list_double2.back(), 2.3);

  my::List<std::string> my_list_string{"Hello", "I'm", "Mike"};
  my::List<std::string> my_list_string2{"Nice", "to", "meet", "you"};
  my_list_string2 = std::move(my_list_string);
  ASSERT_EQ(my_list_string.size(), 0);
  ASSERT_EQ(my_list_string2.size(), 3);
  auto it = my_list_string2.begin();
  auto it_end = my_list_string2.end();
  --it_end;
  ASSERT_EQ(*it, "Hello");
  ASSERT_EQ(*it_end, "Mike");
}
TEST(List_Modifiers, test_clear) {
  my::List<int> my_list_int{777, -3, 1, 0, 5};
  std::list<int> list_int{777, -3, 1, 0, 5};
  my_list_int.clear();
  list_int.clear();
  ASSERT_EQ(my_list_int.size(), list_int.size());
  ASSERT_TRUE(my_list_int.empty());
}

TEST(List_Modifiers, test_insert_push) {
  my::List<int> my_list_int{777, -3, 1, 0, 5};
  std::list<int> list_int{777, -3, 1, 0, 5};
  auto it_my = my_list_int.begin();
  auto it_orig = list_int.begin();
  auto it_my_insert = my_list_int.insert(it_my, 111);
  auto it_orig_insert = list_int.insert(it_orig, 111);
  ASSERT_EQ(*it_my_insert, *it_orig_insert);
  ++it_my;
  ++it_orig;
  auto it_my_insert2 = my_list_int.insert(it_my, 8);
  auto it_orig_insert2 = list_int.insert(it_orig, 8);
  ASSERT_EQ(*it_my_insert2, *it_orig_insert2);
}

TEST(List_Modifiers, test_erase_pop) {
  my::List<std::string> my_list_string{"Hello", "I'm", "Mike"};
  std::list<std::string> list_string{"Hello", "I'm", "Mike"};
  auto it_my = my_list_string.begin();
  auto it_orig = list_string.begin();
  ++it_my;
  ++it_orig;
  my_list_string.erase(it_my);
  list_string.erase(it_orig);
  auto it_my_after_erase = my_list_string.begin();
  auto it_orig_after_erase = list_string.begin();
  ++it_my_after_erase;
  ++it_orig_after_erase;
  ASSERT_EQ(*it_my_after_erase, *it_orig_after_erase);

  my_list_string.erase(it_my_after_erase);
  list_string.erase(it_orig_after_erase);
  auto it_my_after_erase2 = my_list_string.begin();
  auto it_orig_after_erase2 = list_string.begin();
  ASSERT_EQ(*it_my_after_erase2, *it_orig_after_erase2);

  my_list_string.erase(it_my_after_erase2);
  list_string.erase(it_orig_after_erase2);
  ASSERT_TRUE(my_list_string.empty());
  ASSERT_TRUE(list_string.empty());
}

TEST(List_Modifiers, test_sort_merge) {
  my::List<double> my_list_double{0.5, -3.9, 11.5, 2.3};
  my::List<double> my_list_double2{-0.5, 777, 25.9, 33.1};
  std::list<double> list_double{0.5, -3.9, 11.5, 2.3};
  std::list<double> list_double2{-0.5, 777, 25.9, 33.1};
  my_list_double.sort();
  my_list_double2.sort();
  list_double.sort();
  list_double2.sort();
  ASSERT_DOUBLE_EQ(my_list_double.front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.back(), list_double.back());
  ASSERT_DOUBLE_EQ(my_list_double2.front(), list_double2.front());
  ASSERT_DOUBLE_EQ(my_list_double2.back(), list_double2.back());

  my_list_double.merge(my_list_double2);
  list_double.merge(list_double2);
  ASSERT_DOUBLE_EQ(my_list_double.front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.back(), list_double.back());
  ASSERT_TRUE(my_list_double2.empty());
  ASSERT_TRUE(list_double2.empty());
}

TEST(List_Modifiers, test_splice) {
  my::List<char> my_list_char{'a', 'c', 'b'};
  my::List<char> my_list_char2{'1', '!', '4', '5'};
  std::list<char> list_char{'a', 'c', 'b'};
  std::list<char> list_char2{'1', '!', '4', '5'};
  auto it_my = my_list_char.end();
  --it_my;
  auto it_orig = list_char.end();
  --it_orig;
  my_list_char.splice(it_my, my_list_char2);
  list_char.splice(it_orig, list_char2);
  ASSERT_EQ(my_list_char.front(), list_char.front());
  ASSERT_EQ(my_list_char.back(), list_char.back());
  ASSERT_TRUE(my_list_char2.empty());
  ASSERT_TRUE(list_char2.empty());
}

TEST(List_Modifiers, test_reverse) {
  my::List<double> my_list_double{0.5, -3.9, 11.5, 2.3};
  std::list<double> list_double{0.5, -3.9, 11.5, 2.3};
  my_list_double.reverse();
  list_double.reverse();
  ASSERT_DOUBLE_EQ(my_list_double.front(), list_double.front());
  ASSERT_DOUBLE_EQ(my_list_double.back(), list_double.back());

  my::List<std::string> my_list_string{"Hello", "I am", "Mike!"};
  std::list<std::string> list_string{"Hello", "I am", "Mike!"};
  my_list_string.reverse();
  list_string.reverse();
  ASSERT_EQ(my_list_string.front(), list_string.front());
  ASSERT_EQ(my_list_string.back(), list_string.back());
}

TEST(List_Modifiers, test_unique) {
  my::List<int> my_list_int{1, 2, 2, 3, 3, 3, 8, 9, 9, 0, 0, 0};
  std::list<int> list_int{1, 2, 2, 3, 3, 3, 8, 9, 9, 0, 0, 0};
  my_list_int.unique();
  list_int.unique();
  ASSERT_EQ(my_list_int.size(), list_int.size());
  auto it_my = my_list_int.begin();
  auto it_orig = list_int.begin();
  ++it_my;
  ++it_my;
  ++it_orig;
  ++it_orig;
  ASSERT_EQ(*it_my, *it_orig);
}

TEST(Bonus_methods, test_emplace_back) {
  struct TableScore {
    int num;
    std::string name;
    double score;

    TableScore() : num(0), name(""), score(0.0) {}
    TableScore(int p_num, std::string p_name, double p_score)
        : num(p_num), name(std::move(p_name)), score(p_score) {}
  };

  my::List<TableScore> my_list;
  my_list.emplace_back(1, "Steve", 4.5);
  std::list<TableScore> origin_list;
  origin_list.emplace_back(1, "Steve", 4.5);
  ASSERT_EQ(my_list.size(), origin_list.size());

  my_list.pop_back();
  origin_list.pop_back();
  ASSERT_EQ(my_list.size(), origin_list.size());

  my_list.emplace_back(1, "Steve", 4.5);
  my_list.emplace_back(2, "Ben", 3.8);
  my_list.emplace_back(3, "Mary", 4.2);
  ASSERT_EQ(my_list.size(), 3);
  auto my_it = my_list.end();
  --my_it;
  ASSERT_EQ((*my_it).num, 3);
  ASSERT_EQ((*my_it).name, "Mary");
  ASSERT_DOUBLE_EQ((*my_it).score, 4.2);
}

TEST(Bonus_methods, test_emplace_front) {
  struct TableScore {
    int num;
    std::string name;
    double score;

    TableScore() : num(0), name(""), score(0.0) {}
    TableScore(int p_num, std::string p_name, double p_score)
        : num(p_num), name(std::move(p_name)), score(p_score) {}
  };

  my::List<TableScore> my_list;
  my_list.emplace_front(1, "Steve", 4.5);
  std::list<TableScore> origin_list;
  origin_list.emplace_front(1, "Steve", 4.5);
  ASSERT_EQ(my_list.size(), origin_list.size());

  my_list.pop_front();
  origin_list.pop_front();
  ASSERT_EQ(my_list.size(), origin_list.size());

  my_list.emplace_front(1, "Steve", 4.5);
  my_list.emplace_front(2, "Ben", 3.8);
  my_list.emplace_front(3, "Mary", 4.2);
  ASSERT_EQ(my_list.size(), 3);
  auto my_it = my_list.end();
  --my_it;
  ASSERT_EQ((*my_it).num, 1);
  ASSERT_EQ((*my_it).name, "Steve");
  ASSERT_DOUBLE_EQ((*my_it).score, 4.5);
}

TEST(Bonus_methods, test_emplace) {
  struct TableScore {
    int num;
    std::string name;
    double score;

    TableScore() : num(0), name(""), score(0.0) {}
    TableScore(int p_num, std::string p_name, double p_score)
        : num(p_num), name(std::move(p_name)), score(p_score) {}
  };

  my::List<TableScore> my_list;
  my_list.emplace_back(1, "Steve", 4.5);
  my_list.emplace_back(2, "Ben", 3.8);
  my_list.emplace_back(3, "Mary", 4.2);
  std::list<TableScore> origin_list;
  origin_list.emplace_back(1, "Steve", 4.5);
  origin_list.emplace_back(2, "Ben", 3.8);
  origin_list.emplace_back(3, "Mary", 4.2);

  ASSERT_EQ(my_list.size(), origin_list.size());
  auto my_it = my_list.begin();
  ++my_it;
  auto my_it_insert = my_list.emplace(my_it, 4, "Ken", 3.1);
  auto origin_it = origin_list.begin();
  ++origin_it;
  auto origin_it_insert = origin_list.emplace(origin_it, 4, "Ken", 3.1);
  ASSERT_EQ((*my_it_insert).num, (*origin_it_insert).num);
  ASSERT_EQ((*my_it_insert).name, (*origin_it_insert).name);
  ASSERT_DOUBLE_EQ((*my_it_insert).score, (*origin_it_insert).score);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
