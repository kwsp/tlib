cmake_minimum_required(VERSION 2.8.12)
project(tlib CXX)

set(CMAKE_CXX_STANDARD 14)

add_library(tlib STATIC
  tlib.cpp
  tlib.h
)
