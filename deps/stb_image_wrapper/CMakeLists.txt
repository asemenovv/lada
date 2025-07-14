cmake_minimum_required(VERSION 3.31)
project(stb_image)

set(CMAKE_CXX_STANDARD 20)

add_library(stb_image STATIC stb_image.cpp)

target_include_directories(stb_image PUBLIC ${ROOT_FOLDER}/deps/stb_image)

add_library(stb::image ALIAS stb_image)