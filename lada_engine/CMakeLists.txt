cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)

add_library(lada_engine STATIC
        src/app/Application.cpp
        src/renderer/buffers/IndexBuffer.cpp
        src/app/GlCall.cpp
        src/renderer/material/Shader.cpp
        src/renderer/material/Texture.cpp
        src/renderer/buffers/VertexArray.cpp
        src/renderer/buffers/VertexBuffer.cpp
        src/app/EntryPoint.cpp
        src/app/Logger.cpp
        src/platform/glfw/GlfwWindow.cpp
        src/app/layer/LayerStack.cpp
        src/imgui/ImGuiLayer.cpp
        src/app/layer/LayerContext.cpp
        src/app/input/GLFWInput.cpp
        src/renderer/Renderer.cpp
        src/renderer/Mesh.cpp
        src/renderer/material/Material.cpp
        src/renderer/model/ModelLoader.cpp
        src/renderer/model/Model.cpp
        src/renderer/Camera.cpp
        src/assets/AssetManager.cpp
        src/renderer/GraphicsContext.cpp
        src/platform/opengl/OpenGLContext.cpp
        src/app/Window.cpp
        src/app/Window.h
        src/app/ecs/EntityManager.cpp
        src/app/ecs/ComponentArray.cpp
        src/app/ecs/ComponentManager.cpp
        src/app/ecs/SystemManager.cpp
        src/app/ecs/EcsCoordinator.cpp
        src/platform/vulkan/VulkanInstance.cpp
        src/platform/vulkan/VulkanInstance.h
        src/platform/vulkan/VulkanPhysicalDevice.cpp
        src/platform/vulkan/VulkanPhysicalDevice.h
        src/platform/vulkan/VulkanContext.cpp
        src/platform/vulkan/VulkanContext.h
        src/platform/vulkan/VulkanDevice.cpp
        src/platform/vulkan/VulkanDevice.h
        src/platform/vulkan/VulkanSurface.cpp
        src/platform/vulkan/VulkanSurface.h
)

target_include_directories(lada_engine
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_SOURCE_DIR}/deps/GLAD/include
)

target_precompile_headers(lada_engine PUBLIC src/ldpch.h)
set_source_files_properties(
        src/app/MetalTest.mm
        PROPERTIES
        SKIP_PRECOMPILE_HEADERS ON
)

target_compile_definitions(lada_engine PUBLIC GLFW_INCLUDE_NONE)

target_link_libraries(lada_engine
        PUBLIC Vulkan::Vulkan
        PUBLIC GLAD
        PUBLIC glfw
        PUBLIC spdlog::spdlog
        PUBLIC glm::glm
        PUBLIC imgui
        PUBLIC stb_image
        PUBLIC assimp
        PUBLIC yaml-cpp
)
