cmake_minimum_required(VERSION 3.22)
project(nano)

set(CMAKE_CXX_STANDARD 17)
add_executable(nano main.cpp Lexer.cpp Lexer.h AST.h Stack.cpp Stack.h Runner.cpp Runner.h)
