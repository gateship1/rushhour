cmake_minimum_required(VERSION 3.20.0)

message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

project(test_RushHour
    LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR})
    
target_link_libraries(${PROJECT_NAME}
    PRIVATE GameEngine
            Vehicles
            gtest_main)

target_sources(${PROJECT_NAME}
    PRIVATE RushHourTests.cpp)

add_subdirectory(GameEngine)
add_subdirectory(GameEngine/Vehicles)
add_subdirectory(GameEngine/Vehicles/PhysicsEngine)
add_subdirectory(Setup)
add_subdirectory(Solvers)
    
gtest_add_tests(
    TARGET     ${PROJECT_NAME}
    TEST_LIST  RushHour_AllTests)
    
set_tests_properties(${RushHour_AllTests}   PROPERTIES TIMEOUT 10)
