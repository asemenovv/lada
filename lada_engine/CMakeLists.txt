cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
add_library(GLEW::GLEW SHARED IMPORTED)
set_target_properties(GLEW::GLEW PROPERTIES
        IMPORTED_LOCATION "${ROOT_FOLDER}/deps/glew/libGLEW.2.2.0.dylib"
        INTERFACE_INCLUDE_DIRECTORIES "${ROOT_FOLDER}/deps/glew/include"
)

# GLFW
add_library(GLFW::GLFW SHARED IMPORTED)
set_target_properties(GLFW::GLFW PROPERTIES
        IMPORTED_LOCATION "${ROOT_FOLDER}/deps/glfw/libglfw.3.dylib"
        INTERFACE_INCLUDE_DIRECTORIES "${ROOT_FOLDER}/deps/glfw/include"
)

add_library(lada_engine STATIC
        src/app/Application.cpp
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
        src/vendor/stb_image/stb_image.cpp
        src/app/EntryPoint.cpp
        src/app/Log.cpp
)

target_include_directories(lada_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(lada_engine
        PUBLIC GLEW::GLEW
        PUBLIC GLFW::GLFW
        PUBLIC OpenGL::GL
        PUBLIC spdlog::spdlog
        PUBLIC glm::glm
)
