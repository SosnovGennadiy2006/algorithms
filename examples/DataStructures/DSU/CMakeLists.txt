cmake_minimum_required(VERSION 3.14)
project(algorithms_DSU_example LANGUAGES CXX)

include("../../../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    find_package(algorithms REQUIRED)
endif()

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_link_libraries(${PROJECT_NAME} PRIVATE algorithms::algorithms)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(${PROJECT_NAME} algorithms::algorithms)
endif()