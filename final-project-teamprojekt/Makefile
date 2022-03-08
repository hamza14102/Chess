CXX=clang++
INCLUDES=-Iincludes/
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -Werror -pedantic $(INCLUDES)
GUIFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

exec: bin/exec
gui: bin/gui
tests: bin/tests

bin/exec: ./src/driver.cc ./src/ChessGame.cc ./src/board.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/gui: ./src/driver.cc ./src/ChessGame.cc ./src/board.cc ./src/ChessGameGUI.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GUIFLAGS)

bin/tests: tests/tests.cc ./src/ChessGame.cc ./src/board.cc
	$(CXX) $(CXXFLAGS) $^ -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec 

clean:
	rm -fr bin/* 
