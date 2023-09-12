#[=[ Rush Hour C++ vehicles source code #]=]
cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(Vehicles
    LANGUAGES CXX)

add_subdirectory(PhysicsEngine)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/HorizontalVehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/PlayerVehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Vehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/VerticalVehicle.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
           ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine)

target_link_libraries(${PROJECT_NAME}
    PUBLIC PhysicsEngine)

set_target_properties(${PROJECT_NAME}
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
