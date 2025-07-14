cmake_minimum_required(VERSION 3.31)
project(imgui)

set(CMAKE_CXX_STANDARD 20)

add_library(imgui
        ${ROOT_FOLDER}/deps/imgui/imgui.cpp
        ${ROOT_FOLDER}/deps/imgui/imgui_demo.cpp
        ${ROOT_FOLDER}/deps/imgui/imgui_draw.cpp
        ${ROOT_FOLDER}/deps/imgui/imgui_tables.cpp
        ${ROOT_FOLDER}/deps/imgui/imgui_widgets.cpp
        ${ROOT_FOLDER}/deps/imgui/backends/imgui_impl_glfw.cpp
        ${ROOT_FOLDER}/deps/imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(imgui
        PRIVATE
        ${ROOT_FOLDER}/deps/imgui/backends/imgui_impl_glfw.cpp
        ${ROOT_FOLDER}/deps/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${ROOT_FOLDER}/deps/imgui
        ${ROOT_FOLDER}/deps/imgui/backends
        ${ROOT_FOLDER}/deps/glfw/include
)

target_include_directories(imgui PUBLIC ../imgui)