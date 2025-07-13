cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

add_library(lada_engine STATIC
        src/lada.cpp
        src/render/IndexBuffer.cpp
        src/render/Renderer.cpp
        src/render/Shader.cpp
        src/render/Texture.cpp
        src/render/VertexArray.cpp
        src/render/VertexBuffer.cpp
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_tables.cpp
        src/vendor/imgui/imgui_demo.cpp
)

target_link_libraries(lada_engine ../deps/glfw/libglfw3.dylib)
target_link_libraries(lada_engine ../deps/glew/libGLEW.dylib)

#find_package(glfw3 3.4 REQUIRED)
#find_package(GLEW 2.2 REQUIRED)
#include_directories(${GLEW_INCLUDE_DIRS})
#link_libraries(${GLEW_LIBRARIES})
#find_package(OpenGL REQUIRED)
