cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

add_library(lada_engine STATIC
        src/app/Application.cpp
        src/render/IndexBuffer.cpp
        src/render/Renderer.cpp
        src/render/Shader.cpp
        src/render/Texture.cpp
        src/render/VertexArray.cpp
        src/render/VertexBuffer.cpp
        src/app/EntryPoint.cpp
        src/app/Logger.cpp
        src/app/Window.cpp
        src/app/layer/LayerStack.cpp
        src/imgui/ImGuiLayer.cpp
        src/Core.cpp
        src/app/layer/LayerContext.cpp
)

target_include_directories(lada_engine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_SOURCE_DIR}/deps/GLAD/include
)

target_precompile_headers(lada_engine PUBLIC src/ldpch.h)

target_compile_definitions(lada_engine PUBLIC GLFW_INCLUDE_NONE)

target_link_libraries(lada_engine
        PUBLIC GLAD
        PUBLIC glfw
        PUBLIC spdlog::spdlog
        PUBLIC glm::glm
        PUBLIC imgui
        PUBLIC stb_image
)
