DIR_SOURCES = containers
LIB = $(DIR_SOURCES)/my_containers.h
SOURСES = $(DIR_SOURCES)/s21_list.h \
	$(DIR_SOURCES)/s21_stack.h \
	$(DIR_SOURCES)/s21_queue.h \
	$(DIR_SOURCES)/s21_map.h \
	$(DIR_SOURCES)/s21_set.h \
	$(DIR_SOURCES)/s21_multiset.h
DIR_TESTS = tests
NAME_LIST = test_list
NAME_STACK = test_stack
NAME_QUEUE = test_queue
NAME_MAP = test_map
NAME_SET = test_set
NAME_MULTISET = test_multiset
TESTS = $(DIR_TESTS)/$(NAME_LIST).cpp \
	$(DIR_TESTS)/$(NAME_STACK).cpp \
	$(DIR_TESTS)/$(NAME_QUEUE).cpp \
	$(DIR_TESTS)/$(NAME_MAP).cpp \
	$(DIR_TESTS)/$(NAME_SET).cpp \
	$(DIR_TESTS)/$(NAME_MULTISET).cpp
CC := g++ -std=c++17
CFLAGS := -Wall -Werror -Wextra
GCOV := -fprofile-arcs -ftest-coverage

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	GTESTFLAGS=-lgtest -lgtest_main 
	OPENFILE=open
else
	GTESTFLAGS=-lgtest -lgtest_main -lpthread -lrt -lm -lsubunit -ldl
	OPENFILE=xdg-open 
endif

.PHONY: tests

all: tests

tests: test_list test_stack test_queue test_map test_set test_multiset
	make gcov_report

test_list: $(DIR_TESTS)/$(NAME_LIST).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_LIST).cpp $(GTESTFLAGS) -o $(NAME_LIST)
	./$(NAME_LIST)

test_stack: $(DIR_TESTS)/$(NAME_STACK).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_STACK).cpp $(GTESTFLAGS) -o $(NAME_STACK)
	./$(NAME_STACK)

test_queue: $(DIR_TESTS)/$(NAME_QUEUE).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_QUEUE).cpp $(GTESTFLAGS) -o $(NAME_QUEUE)
	./$(NAME_QUEUE)

test_map: $(DIR_TESTS)/$(NAME_MAP).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_MAP).cpp $(GTESTFLAGS) -o $(NAME_MAP)
	./$(NAME_MAP)

test_set: $(DIR_TESTS)/$(NAME_SET).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_SET).cpp $(GTESTFLAGS) -o $(NAME_SET)
	./$(NAME_SET)

test_multiset: $(DIR_TESTS)/$(NAME_MULTISET).cpp
	$(CC) $(GCOV) $(DIR_TESTS)/$(NAME_MULTISET).cpp $(GTESTFLAGS) -o $(NAME_MULTISET)
	./$(NAME_MULTISET)

gcov_report: 
	lcov -t "GcovReport" -o GcovReport.info -c -d . --no-external
	genhtml  -o report GcovReport.info
	rm -f $(NAME_LIST) $(NAME_STACK) $(NAME_QUEUE) $(NAME_VECTOR) $(NAME_ARRAY) $(NAME_MAP) $(NAME_SET) $(NAME_MULTISET)
	rm -f *.gcno *.gcda *.info
	$(OPENFILE) ./report/index.html

clean:
	rm -f *.o *.a a.out *.txt
	rm -f $(NAME_LIST) $(NAME_STACK) $(NAME_QUEUE) $(NAME_VECTOR) $(NAME_ARRAY) $(NAME_MAP) $(NAME_SET) $(NAME_MULTISET)
	rm -f *.gcno *.gcda *.info
	rm -rf ./report
	rm -rf *.txt

rebuild: clean all

#----Checking----
linter:
	echo "--------Linter Cpplint.py--------"
	python3 cpplint.py --extensions=cpp $(TESTS) $(LIB) $(SOURСES)
leaks:
	echo "--------Leaks Checking--------"
	CK_FORK=no leaks -atExit -- ./$(NAME_LIST) >leaks-out.txt 2>&1
	CK_FORK=no leaks -atExit -- ./$(NAME_STACK) >>leaks-out.txt 2>&1
	CK_FORK=no leaks -atExit -- ./$(NAME_QUEUE) >>leaks-out.txt 2>&1
	CK_FORK=no leaks -atExit -- ./$(NAME_MAP) >>leaks-out.txt 2>&1
	CK_FORK=no leaks -atExit -- ./$(NAME_SET) >>leaks-out.txt 2>&1
	CK_FORK=no leaks -atExit -- ./$(NAME_MULTISET) >>leaks-out.txt 2>&1
cppcheck:
	echo "--------Static Code Checking--------"
	cppcheck --enable=all --suppress=missingIncludeSystem ./
valgrind:
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_LIST) >valgrind-out.txt 2>&1
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_STACK) >>valgrind-out.txt 2>&1
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_QUEUE) >>valgrind-out.txt 2>&1
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_MAP) >>valgrind-out.txt 2>&1
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_SET) >>valgrind-out.txt 2>&1
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(NAME_MULTISET) >>valgrind-out.txt 2>&1
