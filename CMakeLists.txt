cmake_minimum_required(VERSION 3.31)
project(lada)

set("ROOT_FOLDER" ${PROJECT_SOURCE_DIR})

include_directories("${PROJECT_SOURCE_DIR}/lada_engine/src")

add_subdirectory(lada_engine)
add_subdirectory(lada_sandbox)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/glm)
add_subdirectory(deps/imgui)