cmake_minimum_required(VERSION 3.17)
project(alang)

set(CMAKE_CXX_STANDARD 20)

add_executable(alang main.cpp helpers.cpp parser.cpp)