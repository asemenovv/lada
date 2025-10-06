cmake_minimum_required(VERSION 3.31)
project(lada)

set("ROOT_FOLDER" ${PROJECT_SOURCE_DIR})

include_directories("${PROJECT_SOURCE_DIR}/lada_engine/src")

#add_definitions(-DSPDLOG_FMT_EXTERNAL=0)

add_subdirectory(lada_engine)
add_subdirectory(lada_sandbox)
add_subdirectory(svarozhich)
add_subdirectory(deps/entt)
add_subdirectory(deps/fmt)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/KDDockWidgets)
add_subdirectory(deps/glm)
add_subdirectory(deps/imgui_wrapper)
add_subdirectory(deps/stb_image_wrapper)
add_subdirectory(deps/GLFW)
add_subdirectory(deps/GLAD)
add_subdirectory(deps/assimp)
add_subdirectory(deps/tinyobjloader)
add_subdirectory(deps/yaml-cpp)

################################## Node Editor (Qt) ##################################
set(CMAKE_PREFIX_PATH "~/Qt/6.9.2/macos")
add_subdirectory(deps/nodeeditor)
################################## Node Editor (Qt) ##################################

####################################### shaderc #######################################
add_subdirectory(deps/spirv-headers)
add_subdirectory(deps/spirv-tools)
add_subdirectory(deps/glslang)
set(SPIRV-Headers_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/spirv-headers CACHE PATH "" FORCE)
set(SPIRV-Tools_SOURCE_DIR   ${CMAKE_SOURCE_DIR}/deps/spirv-tools   CACHE PATH "" FORCE)
set(SHADERC_SKIP_TESTS     ON CACHE BOOL "" FORCE)
set(SHADERC_ENABLE_TESTS   OFF CACHE BOOL "" FORCE)
set(SHADERC_SKIP_EXAMPLES  ON CACHE BOOL "" FORCE)
add_subdirectory(deps/shaderc)
####################################### shaderc #######################################
