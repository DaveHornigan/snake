cmake_minimum_required(VERSION 3.23)
project(snake_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(snake_game main.cpp inc/Map.h inc/Snake.h inc/Fruit.h main.h)
