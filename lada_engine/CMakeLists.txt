cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(build_shaders
        COMMAND ./compile.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

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
        src/platform/opengl/OpenGLContext.cpp
        src/app/Window.cpp
        src/app/ecs/EntityManager.cpp
        src/app/ecs/ComponentArray.cpp
        src/app/ecs/ComponentManager.cpp
        src/app/ecs/SystemManager.cpp
        src/app/ecs/EcsCoordinator.cpp
        src/platform/vulkan/device/VulkanInstance.cpp
        src/platform/vulkan/device/VulkanPhysicalDevice.cpp
        src/platform/vulkan/VulkanGraphicsContext.cpp
        src/platform/vulkan/device/VulkanDevice.cpp
        src/platform/vulkan/device/VulkanSurface.cpp
        src/platform/vulkan/VulkanSwapChain.cpp
        src/renderer/SwapChain.cpp
        src/platform/opengl/OpenGLSwapChain.cpp
        src/renderer/GraphicsApiFactory.cpp
        src/platform/vulkan/buffers/VulkanImage.cpp
        src/platform/vulkan/pipeline/VulkanShader.cpp
        src/platform/vulkan/pipeline/VulkanShaderCompiler.cpp
        src/platform/vulkan/pipeline/VulkanPipeline.cpp
        src/platform/vulkan/pipeline/VulkanPipeline.h
        src/platform/vulkan/pipeline/VulkanPipelineLayout.cpp
        src/platform/vulkan/pipeline/VulkanPipelineLayout.h
        src/platform/vulkan/pipeline/VulkanRenderPass.cpp
        src/platform/vulkan/pipeline/VulkanRenderPass.h
        src/platform/vulkan/VulkanFramebuffer.cpp
        src/platform/vulkan/VulkanFramebuffer.h
        src/platform/vulkan/commands/VulkanCommandPool.cpp
        src/platform/vulkan/commands/VulkanCommandPool.h
        src/platform/vulkan/commands/VulkanCommandBuffer.cpp
        src/platform/vulkan/commands/VulkanCommandBuffer.h
        src/renderer/CommandBuffer.cpp
        src/renderer/CommandBuffer.h
        src/renderer/RenderPass.cpp
        src/renderer/RenderPass.h
        src/renderer/Pipeline.cpp
        src/renderer/Pipeline.h
        src/platform/vulkan/sync/VulkanSemaphore.cpp
        src/platform/vulkan/sync/VulkanSemaphore.h
        src/platform/vulkan/sync/VulkanFence.cpp
        src/platform/vulkan/sync/VulkanFence.h
        src/scene/Scene.cpp
        src/scene/Scene.h
        src/core/UUID.cpp
        src/core/UUID.h
        src/renderer/RenderStatus.h
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

target_compile_definitions(lada_engine PUBLIC GLFW_INCLUDE_NONE IMGUI_IMPL_OPENGL_LOADER_GLAD)

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
        PUBLIC shaderc
)
add_dependencies(lada_engine build_shaders)
