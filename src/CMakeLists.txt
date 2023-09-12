#[=[ Rush Hour source code #]=]
cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(Game
    LANGUAGES CXX)

add_subdirectory(GameEngine)
add_subdirectory(Setup)
add_subdirectory(Solvers)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Game.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Game
    PUBLIC GameEngine
           Setup
           Solvers)

set_target_properties(${PROJECT_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
