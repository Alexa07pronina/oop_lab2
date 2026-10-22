cmake_minimum_required(VERSION 3.16)
project(Lab2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


add_executable(lab2 
    src/main.cpp
    src/custom_string.cpp
)

target_include_directories(lab2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_options(lab2 PRIVATE -Wall -Wextra -Wpedantic)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Тесты
add_executable(lab2_tests
    tests/test_lab2.cpp
    src/custom_string.cpp
)

target_include_directories(lab2_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(lab2_tests GTest::gtest_main)
target_compile_options(lab2_tests PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_test(NAME Lab2Tests COMMAND lab2_tests)