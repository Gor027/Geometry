cmake_minimum_required(VERSION 3.17)
project(Geometry)

set(CMAKE_CXX_STANDARD 17)

add_executable(Geometry main.cpp geometry.cc geometry.h)

#add_executable(Geometry test.cpp)