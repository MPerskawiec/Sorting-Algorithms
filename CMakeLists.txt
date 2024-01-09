cmake_minimum_required(VERSION 3.14)
project(Sorting)

set (SRC main.cpp Algorytmy_Sortowania.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} ${SRC})