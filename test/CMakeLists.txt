
include_directories(
  ./
  ../tlib
)

add_executable(ttest main.cpp)

target_link_libraries(
  ttest
  tlib
)
