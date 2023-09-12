message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

cmake_minimum_required(VERSION 3.20.0)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test_movement.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Vehicles)
