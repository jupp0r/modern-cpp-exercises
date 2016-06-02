cmake_minimum_required(VERSION 3.5)

add_subdirectory("../googletest" ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(
  exercise

  exercise.cpp
  exercise.h
  test.cpp
  )

target_link_libraries(exercise gmock_main)
target_include_directories(exercise PRIVATE "../googletest/googletest/include")
set_property(TARGET exercise PROPERTY CXX_STANDARD 14)
