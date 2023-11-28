
CC=gcc --coverage -g -O0
CPP=g++ --coverage -g -O0
LEX=/usr/local/bin/flex
YACC=/usr/local/bin/bison

clean:
	rm *.o
	rm -rf *.dSYM
	rm -rf *.dcno
	rm *.gcov
	rm *.gcda
	rm -rf html
	rm coverage.info

#coverage: 
#	lcov --capture --directory . --output-file coverage.info
#	genhtml coverage.info --output-directory html

yale_column.o: yale_column.cpp yale_column.hpp
	gcc --coverage -g -O0 yale_column.cpp -c

yale_measure.o: yale_measure.cpp yale_measure.hpp
	gcc --coverage -g -O0 yale_measure.cpp -c

yale_object.o: yale_object.cpp yale_object.hpp
	gcc --coverage -g -O0 yale_object.cpp -c

yale_rect.o: yale_rect.cpp yale_rect.hpp
	gcc --coverage -g -O0 yale_rect.cpp -c

yale_score.o: yale_score.cpp yale_score.hpp
	gcc --coverage -g -O0 yale_score.cpp -c

yale_staff.o: yale_staff.cpp yale_staff.hpp
	gcc --coverage -g -O0 yale_staff.cpp -c

yale_time_sig.o: yale_time_sig.cpp yale_time_sig.hpp
	gcc --coverage -g -O0 yale_time_sig.cpp -c

all: yale_column.o yale_measure.o yale_object.o yale_rect.o yale_score.o yale_staff.o yale_time_sig.o
	ar rcs liblaban.a yale_column.o yale_measure.o yale_object.o yale_rect.o yale_score.o yale_staff.o yale_time_sig.o 

json_tests: lexer.o parser.o sym_table.hpp parse_tree.hpp json_tests.cpp 
	g++ --coverage -g -O0 -lgtest -lgtest_main -ljson json_tests.cpp -o json_tests -std=c++14
	gcov json_tests.cpp parse_tree.cpp

check: json_tests
