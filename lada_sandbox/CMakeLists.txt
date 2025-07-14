cmake_minimum_required(VERSION 3.31)
project(lada_sandbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(lada_sandbox
        src/main.cpp
        src/DemoApp.cpp
)

include_directories("${ROOT_FOLDER}/lada_engine/src")

target_link_libraries(lada_sandbox
        PRIVATE lada_engine
        PRIVATE spdlog::spdlog
        PRIVATE glm::glm
        PRIVATE imgui
)
