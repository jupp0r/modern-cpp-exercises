cmake_minimum_required(VERSION 3.3)

add_subdirectory("../googletest" ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(
  exercise0

  exercise.cpp
  slides.cpp
  )

if(MSVC)
    # We explicitly disable the non-standard extensions of visual studio to trigger a compilation error for std::vector<bool>
    target_compile_options(exercise0 PUBLIC "/W4" "/wd4189" "/Za")
    target_compile_options(exercise0 PUBLIC "/MT$<$<STREQUAL:$<CONFIGURATION>,Debug>:d>")
endif()
target_link_libraries(exercise0 gmock_main)
target_include_directories(exercise0 PRIVATE "../googletest/googletest/include")
set_property(TARGET exercise0 PROPERTY CXX_STANDARD 14)
