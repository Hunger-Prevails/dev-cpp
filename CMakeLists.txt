cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json 3.12.0 REQUIRED)

add_executable(code code.cpp)

target_link_libraries(code PRIVATE nlohmann_json::nlohmann_json)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/res)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/)