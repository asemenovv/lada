cmake_minimum_required(VERSION 3.31)
project(LadaEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(LadaEngine
        Log.cpp
        src/IndexBuffer.cpp
        src/VertexBuffer.cpp
        src/Renderer.cpp
        src/Application.cpp
        src/VertexArray.cpp
        src/Shader.cpp
        src/vendor/stb_image/stb_image.cpp
        src/Texture.cpp
        src/vendor/imgui/imgui_impl_opengl3.cpp
        src/vendor/imgui/imgui_impl_glfw.cpp
        src/vendor/imgui/imgui.cpp
        src/vendor/imgui/imgui_draw.cpp
        src/vendor/imgui/imgui_widgets.cpp
        src/vendor/imgui/imgui_tables.cpp
        src/ApplicationBase.cpp
        src/DemoApp.cpp
)

find_package(glfw3 3.4 REQUIRED)

find_package(GLEW 2.2 REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)

target_link_libraries(LadaEngine glfw ${GLEW_LIBRARIES} OpenGL::GL)
