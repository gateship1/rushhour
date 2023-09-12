#[=[ Rush Hour C++ solver engine source code #]=]
cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(Solvers
    LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/AStar.cpp
            ${CMAKE_CURRENT_LIST_DIR}/BFS.cpp
            ${CMAKE_CURRENT_LIST_DIR}/DFS.cpp
            ${CMAKE_CURRENT_LIST_DIR}/heuristics.cpp
            ${CMAKE_CURRENT_LIST_DIR}/RandomWalk.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Solver.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME}
    PUBLIC GameEngine)

set_target_properties(${PROJECT_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
