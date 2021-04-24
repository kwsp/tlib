cmake_minimum_required(VERSION 3.16)

project(tlib_test CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#Requires CMake 3.16+
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(
  ./
  ../tlib
)

# Vector
add_executable(
  vector_test 
  vector_test.cpp
)
target_link_libraries(
  vector_test
  gtest_main
)

# List
add_executable(
  list_test 
  list_test.cpp
)
target_link_libraries(
  list_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_test)
