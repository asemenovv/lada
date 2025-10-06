cmake_minimum_required(VERSION 3.31)
project(lada_engine)

set(CMAKE_CXX_STANDARD 20)

add_custom_target(build_shaders
        COMMAND ./compile.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

find_package(Vulkan REQUIRED)

file(GLOB_RECURSE LADA_ENGINE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
file(GLOB_RECURSE LADA_ENGINE_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_library(lada_engine STATIC ${LADA_ENGINE_SOURCES} ${LADA_ENGINE_HEADERS})

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
        PUBLIC tinyobjloader
        PUBLIC yaml-cpp
        PUBLIC shaderc
        PUBLIC EnTT::EnTT
)
add_dependencies(lada_engine build_shaders)
