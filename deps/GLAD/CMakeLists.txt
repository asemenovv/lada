cmake_minimum_required(VERSION 3.31)
project(GLAD LANGUAGES C)

set(CMAKE_CXX_STANDARD 20)

add_library(GLAD ${CMAKE_SOURCE_DIR}/deps/GLAD/src/glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_SOURCE_DIR}/deps/GLAD/include)
