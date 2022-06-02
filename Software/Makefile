CXX = /usr/bin/g++
LDFLAGS =
CPPFLAGS =
INC =
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -O2 -D_GLIBCXX_ASSERTIONS -g



%.o: %.cpp
	${CXX} ${CXXFLAGS} -I . -c $*.cpp


main: nfa_pointer.o korotkov_nfa.o graphMaker.o main.cpp
	${CXX} ${CXXFLAGS} -I . $^ -o main

clear:
	rm -rf *.o
