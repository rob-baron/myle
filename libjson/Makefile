
CC=gcc --coverage -g -O0
CPP=g++ --coverage -g -O0
LEX=/usr/local/bin/flex
YACC=/usr/local/bin/bison

clean:
	rm lexer.c
	rm lexer.h
	rm parser.c
	rm parser.h
	rm *.o
	rm -rf *.dSYM
	rm -rf *.dcno
	rm *.gcov
	rm *.gcda
	rm -rf html
	rm coverage.info
	rm json_tests 

#coverage: 
#	lcov --capture --directory . --output-file coverage.info
#	genhtml coverage.info --output-directory html

lexer.c: lexer.l parser.h
	LEX --nowarn --outfile=lexer.c --header-file=lexer.h lexer.l

parser.c: parser.y
	YACC --defines=parser.h -o parser.c parser.y

parser.h: parser.y
	YACC --defines=parser.h -o parser.c parser.y

lexer.o: lexer.c
	gcc --coverage -g -O0 lexer.c -c

parser.o: parser.c
	gcc --coverage -g -O0 parser.c -c

libjson.o: lexer.o parser.o parser.c sym_table.hpp sym_table.cpp parse_tree.hpp parse_tree.cpp
	g++ -g -c -O0 -std=c++14 lexer.o parser.o parse_tree.cpp -o libjson.o

all: libjson.o
	ar rcs libjson.a libjson.o

json_tests: lexer.o parser.o sym_table.hpp parse_tree.hpp json_tests.cpp 
	g++ --coverage -g -O0 -lgtest -lgtest_main -ljson json_tests.cpp -o json_tests -std=c++14
	gcov json_tests.cpp parse_tree.cpp

check: json_tests
