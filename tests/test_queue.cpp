#include <gtest/gtest.h>

#include <queue>

#include "../containers/my_containers.h"

TEST(Queue_Constructors, default_constructor) {
  my::Queue<int> my_queue_int;
  ASSERT_TRUE(my_queue_int.empty());
  ASSERT_EQ(my_queue_int.size(), 0);

  my::Queue<size_t> my_queue_size_t;
  ASSERT_TRUE(my_queue_size_t.empty());
  ASSERT_EQ(my_queue_size_t.size(), 0);

  my::Queue<double> my_queue_double;
  ASSERT_TRUE(my_queue_double.empty());
  ASSERT_EQ(my_queue_double.size(), 0);

  my::Queue<char> my_queue_char;
  ASSERT_TRUE(my_queue_char.empty());
  ASSERT_EQ(my_queue_char.size(), 0);

  my::Queue<std::string> my_queue_string;
  ASSERT_TRUE(my_queue_string.empty());
  ASSERT_EQ(my_queue_string.size(), 0);
}

TEST(Queue_Constructors, initializer_queue_constructor) {
  my::Queue<int> my_queue_int{777, -3, 1, 2, 5};
  ASSERT_EQ(my_queue_int.size(), 5);
  ASSERT_EQ(my_queue_int.back(), 5);
  ASSERT_EQ(my_queue_int.front(), 777);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Mike"};
  ASSERT_EQ(my_queue_string.size(), 3);
  ASSERT_EQ(my_queue_string.back(), "Mike");
  ASSERT_EQ(my_queue_string.front(), "Hello");
}

TEST(Queue_Constructors, copy_constructor) {
  my::Queue<int> my_queue_int{777, -3, 1, 2, 5};
  my::Queue<int> my_queue_int2(my_queue_int);
  ASSERT_EQ(my_queue_int.size(), 5);
  ASSERT_EQ(my_queue_int.back(), 5);
  ASSERT_EQ(my_queue_int.front(), 777);
  ASSERT_EQ(my_queue_int2.size(), 5);
  ASSERT_EQ(my_queue_int2.back(), 5);
  ASSERT_EQ(my_queue_int2.front(), 777);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Mike"};
  my::Queue<std::string> my_queue_string2(my_queue_string);
  ASSERT_EQ(my_queue_string.size(), 3);
  ASSERT_EQ(my_queue_string.back(), "Mike");
  ASSERT_EQ(my_queue_string.front(), "Hello");
  ASSERT_EQ(my_queue_string2.size(), 3);
  ASSERT_EQ(my_queue_string2.back(), "Mike");
  ASSERT_EQ(my_queue_string2.front(), "Hello");
}

TEST(Queue_Constructors, move_constructor) {
  my::Queue<int> my_queue_int{777, -3, 1, 2, 5};
  my::Queue<int> my_queue_int2(std::move(my_queue_int));
  ASSERT_EQ(my_queue_int.size(), 0);
  ASSERT_EQ(my_queue_int2.size(), 5);
  ASSERT_EQ(my_queue_int2.back(), 5);
  ASSERT_EQ(my_queue_int2.front(), 777);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Mike"};
  my::Queue<std::string> my_queue_string2(std::move(my_queue_string));
  ASSERT_EQ(my_queue_string.size(), 0);
  ASSERT_EQ(my_queue_string2.size(), 3);
  ASSERT_EQ(my_queue_string2.back(), "Mike");
  ASSERT_EQ(my_queue_string2.front(), "Hello");
}

TEST(Queue_Overload, assignment_operator) {
  my::Queue<int> my_queue_int{777, -3, 1, 2, 5};
  my::Queue<int> my_queue_int2;
  my_queue_int2 = my_queue_int;
  ASSERT_EQ(my_queue_int.size(), 5);
  ASSERT_EQ(my_queue_int.back(), 5);
  ASSERT_EQ(my_queue_int.front(), 777);
  ASSERT_EQ(my_queue_int2.size(), 5);
  ASSERT_EQ(my_queue_int2.back(), 5);
  ASSERT_EQ(my_queue_int2.front(), 777);

  my::Queue<double> my_queue_double{0.5, -3.9, 1.5, 2.3};
  my::Queue<double> my_queue_double2{100.1, 100.2};
  my_queue_double2 = my_queue_double;
  ASSERT_EQ(my_queue_double.size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double.back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double.front(), 0.5);
  ASSERT_EQ(my_queue_double2.size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double2.back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double2.front(), 0.5);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Mike"};
  my::Queue<std::string> my_queue_string2{"Nice", "to", "meet", "you"};
  my_queue_string2 = std::move(my_queue_string);
  ASSERT_EQ(my_queue_string.size(), 0);
  ASSERT_EQ(my_queue_string2.size(), 3);
  ASSERT_EQ(my_queue_string2.back(), "Mike");
  ASSERT_EQ(my_queue_string2.front(), "Hello");
}

TEST(Queue_Modifiers, test_push_pop) {
  my::Queue<int> my_queue_int({777, -3, 1, 0, 5});
  std::queue<int> queue_int({777, -3, 1, 0, 5});
  my_queue_int.push(9);
  queue_int.push(9);
  ASSERT_EQ(my_queue_int.back(), queue_int.back());

  my_queue_int.pop();
  queue_int.pop();
  ASSERT_EQ(my_queue_int.front(), queue_int.front());

  my::Queue<std::string> my_queue_string({"Hello"});
  std::queue<std::string> queue_string({"Hello"});
  my_queue_string.pop();
  queue_string.pop();
  ASSERT_TRUE(my_queue_string.empty());
  ASSERT_TRUE(queue_string.empty());

  my_queue_string.push("Mike");
  queue_string.push("Mike");
  ASSERT_EQ(my_queue_string.back(), queue_string.back());
  ASSERT_EQ(my_queue_string.front(), queue_string.front());
}

TEST(Queue_Modifiers, test_swap) {
  my::Queue<double> my_queue_double{0.5, -3.9, 1.5, 2.3};
  my::Queue<double> my_queue_double2{100.1, 100.2};
  my_queue_double2.swap(my_queue_double);
  ASSERT_EQ(my_queue_double.size(), 2);
  ASSERT_DOUBLE_EQ(my_queue_double.back(), 100.2);
  ASSERT_DOUBLE_EQ(my_queue_double.front(), 100.1);
  ASSERT_EQ(my_queue_double2.size(), 4);
  ASSERT_DOUBLE_EQ(my_queue_double2.back(), 2.3);
  ASSERT_DOUBLE_EQ(my_queue_double2.front(), 0.5);

  my::Queue<std::string> my_queue_string{"Hello", "I'm", "Mike"};
  my::Queue<std::string> my_queue_string2{"Nice", "to", "meet", "you"};
  my_queue_string2.swap(my_queue_string);
  ASSERT_EQ(my_queue_string.size(), 4);
  ASSERT_EQ(my_queue_string.back(), "you");
  ASSERT_EQ(my_queue_string.front(), "Nice");
  ASSERT_EQ(my_queue_string2.size(), 3);
  ASSERT_EQ(my_queue_string2.back(), "Mike");
  ASSERT_EQ(my_queue_string2.front(), "Hello");
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

  my::Queue<TableScore> my_queue;
  my_queue.emplace_back(1, "Steve", 4.5);
  std::queue<TableScore> origin_queue;
  origin_queue.emplace(1, "Steve", 4.5);
  ASSERT_EQ(my_queue.size(), origin_queue.size());

  my_queue.pop();
  origin_queue.pop();
  ASSERT_EQ(my_queue.size(), origin_queue.size());

  my_queue.emplace_back(1, "Steve", 4.5);
  my_queue.emplace_back(2, "Ben", 3.8);
  my_queue.emplace_back(3, "Mary", 4.2);
  ASSERT_EQ(my_queue.size(), 3);
  ASSERT_EQ(my_queue.front().num, 1);
  ASSERT_EQ(my_queue.front().name, "Steve");
  ASSERT_DOUBLE_EQ(my_queue.front().score, 4.5);
  ASSERT_EQ(my_queue.back().num, 3);
  ASSERT_EQ(my_queue.back().name, "Mary");
  ASSERT_DOUBLE_EQ(my_queue.back().score, 4.2);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
