cmake_minimum_required(VERSION 3.28)
project(Scanner)

set(CMAKE_CXX_STANDARD 17)
add_executable(Scanner main.cpp compiler.h tokens.cpp compiler.cpp "lexical analyzer.cpp")
