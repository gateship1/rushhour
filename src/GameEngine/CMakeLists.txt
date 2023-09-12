#[=[ Rush Hour C++ game engine source code #]=]
cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(GameEngine
    LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

add_subdirectory(Vehicles)

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Board.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
           ${CMAKE_CURRENT_LIST_DIR}/Vehicles
           ${CMAKE_CURRENT_LIST_DIR}/Vehicles/PhysicsEngine)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Vehicles)

set_target_properties(${PROJECT_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
