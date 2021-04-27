cmake_minimum_required(VERSION 3.16)

project(tlib_test CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include_directories(
  ./
  ../tlib)

#Requires CMake 3.16+
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
  )

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

function(add_test src_file)
  get_filename_component(fname ${src_file} NAME_WE)
  add_executable(
    ${fname} 
    ${src_file})
  target_link_libraries(
    ${fname}
    gtest_main)
  gtest_discover_tests(${fname})
endfunction()

add_test(vector_test.cpp)
add_test(list_test.cpp)
