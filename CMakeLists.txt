cmake_minimum_required(VERSION 3.29)
project(Dewarp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dewarp main.cpp
        include/utils.h
        utils.cpp)
