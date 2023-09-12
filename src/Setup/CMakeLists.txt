cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(Setup
    LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/SetupDefaultBoard.cpp
            ${CMAKE_CURRENT_LIST_DIR}/SetupFromCmdLine.cpp
            ${CMAKE_CURRENT_LIST_DIR}/SetupFromFile.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Setup.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME}
    PUBLIC GameEngine)

set_target_properties(${PROJECT_NAME}
PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
           LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
           RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
