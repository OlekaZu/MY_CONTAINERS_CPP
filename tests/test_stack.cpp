#include <gtest/gtest.h>

#include <stack>

#include "../containers/my_containers.h"

TEST(Stack_Constructors, default_constructor) {
  my::Stack<int> my_stack_int;
  ASSERT_TRUE(my_stack_int.empty());
  ASSERT_EQ(my_stack_int.size(), 0);

  my::Stack<size_t> my_stack_size_t;
  ASSERT_TRUE(my_stack_size_t.empty());
  ASSERT_EQ(my_stack_size_t.size(), 0);

  my::Stack<double> my_stack_double;
  ASSERT_TRUE(my_stack_double.empty());
  ASSERT_EQ(my_stack_double.size(), 0);

  my::Stack<char> my_stack_char;
  ASSERT_TRUE(my_stack_char.empty());
  ASSERT_EQ(my_stack_char.size(), 0);

  my::Stack<std::string> my_stack_string;
  ASSERT_TRUE(my_stack_string.empty());
  ASSERT_EQ(my_stack_string.size(), 0);
}

TEST(Stack_Constructors, initializer_stack_constructor) {
  my::Stack<int> my_stack_int{777, -3, 1, 2, 5};
  ASSERT_EQ(my_stack_int.size(), 5);
  ASSERT_EQ(my_stack_int.top(), 5);

  my::Stack<std::string> my_stack_string{"Hello", "I'm", "Mike"};
  ASSERT_EQ(my_stack_string.size(), 3);
  ASSERT_EQ(my_stack_string.top(), "Mike");
}

TEST(Stack_Constructors, copy_constructor) {
  my::Stack<int> my_stack_int{777, -3, 1, 2, 5};
  my::Stack<int> my_stack_int2(my_stack_int);
  ASSERT_EQ(my_stack_int.size(), 5);
  ASSERT_EQ(my_stack_int.top(), 5);
  ASSERT_EQ(my_stack_int2.size(), 5);
  ASSERT_EQ(my_stack_int2.top(), 5);

  my::Stack<std::string> my_stack_string{"Hello", "I'm", "Mike"};
  my::Stack<std::string> my_stack_string2(my_stack_string);
  ASSERT_EQ(my_stack_string.size(), 3);
  ASSERT_EQ(my_stack_string.top(), "Mike");
  ASSERT_EQ(my_stack_string2.size(), 3);
  ASSERT_EQ(my_stack_string2.top(), "Mike");
}

TEST(Stack_Constructors, move_constructor) {
  my::Stack<int> my_stack_int{777, -3, 1, 2, 5};
  my::Stack<int> my_stack_int2(std::move(my_stack_int));
  ASSERT_EQ(my_stack_int.size(), 0);
  ASSERT_EQ(my_stack_int2.size(), 5);
  ASSERT_EQ(my_stack_int2.top(), 5);

  my::Stack<std::string> my_stack_string{"Hello", "I'm", "Mike"};
  my::Stack<std::string> my_stack_string2(std::move(my_stack_string));
  ASSERT_EQ(my_stack_string.size(), 0);
  ASSERT_EQ(my_stack_string2.size(), 3);
  ASSERT_EQ(my_stack_string2.top(), "Mike");
}

TEST(stack_Overload, assignment_operator_swap) {
  my::Stack<int> my_stack_int{777, -3, 1, 2, 5};
  my::Stack<int> my_stack_int2;
  my_stack_int2 = my_stack_int;
  ASSERT_EQ(my_stack_int.size(), 5);
  ASSERT_EQ(my_stack_int.top(), 5);
  ASSERT_EQ(my_stack_int2.size(), 5);
  ASSERT_EQ(my_stack_int2.top(), 5);

  my::Stack<double> my_stack_double{0.5, -3.9, 1.5, 2.3};
  my::Stack<double> my_stack_double2{100.1, 100.2};
  my_stack_double2 = my_stack_double;
  ASSERT_EQ(my_stack_double.size(), 4);
  ASSERT_DOUBLE_EQ(my_stack_double.top(), 2.3);
  ASSERT_EQ(my_stack_double2.size(), 4);
  ASSERT_DOUBLE_EQ(my_stack_double2.top(), 2.3);

  my::Stack<std::string> my_stack_string{"Hello", "I'm", "Mike"};
  my::Stack<std::string> my_stack_string2{"Nice", "to", "meet", "you"};
  my_stack_string2 = std::move(my_stack_string);
  ASSERT_EQ(my_stack_string.size(), 0);
  ASSERT_EQ(my_stack_string2.size(), 3);
  ASSERT_EQ(my_stack_string2.top(), "Mike");
}

TEST(Stack_Modifiers, test_push_pop) {
  my::Stack<int> my_stack_int({777, -3, 1, 0, 5});
  std::stack<int> stack_int({777, -3, 1, 0, 5});
  my_stack_int.push(9);
  stack_int.push(9);
  ASSERT_EQ(my_stack_int.top(), stack_int.top());

  my_stack_int.pop();
  stack_int.pop();
  ASSERT_EQ(my_stack_int.top(), stack_int.top());

  my::Stack<std::string> my_stack_string({"Hello"});
  std::stack<std::string> stack_string({"Hello"});
  my_stack_string.pop();
  stack_string.pop();
  ASSERT_TRUE(my_stack_string.empty());
  ASSERT_TRUE(stack_string.empty());

  my_stack_string.push("Mike");
  stack_string.push("Mike");
  ASSERT_EQ(my_stack_string.top(), stack_string.top());
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

  my::Stack<TableScore> my_stack;
  my_stack.emplace_front(1, "Steve", 4.5);
  std::stack<TableScore> origin_stack;
  origin_stack.emplace(1, "Steve", 4.5);
  ASSERT_EQ(my_stack.size(), origin_stack.size());

  my_stack.pop();
  origin_stack.pop();
  ASSERT_EQ(my_stack.size(), origin_stack.size());

  my_stack.emplace_front(1, "Steve", 4.5);
  my_stack.emplace_front(2, "Ben", 3.8);
  my_stack.emplace_front(3, "Mary", 4.2);
  ASSERT_EQ(my_stack.size(), 3);
  ASSERT_EQ(my_stack.top().num, 3);
  ASSERT_EQ(my_stack.top().name, "Mary");
  ASSERT_DOUBLE_EQ(my_stack.top().score, 4.2);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
