cmake_minimum_required(VERSION 3.20)
project(140_word_break)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2 -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SRC_DIR "${CMAKE_CURRENT_LIST_DIR}")

add_executable(main "${SRC_DIR}/main.cpp")
