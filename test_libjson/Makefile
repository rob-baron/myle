CC=gcc --coverage -g -O0
CPP=g++ --coverage -g -O0
LEX=/usr/local/bin/flex
YACC=/usr/local/bin/bison

all: .cpp 
	g++ --coverage -g -O0 -lgtest -lgtest_main -ljson .cpp -o json_tests2  -std=c++14
	gcov json_tests.cpp parse_tree.cpp

