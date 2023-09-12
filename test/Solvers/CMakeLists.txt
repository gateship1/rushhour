message(STATUS "Added sub_directory: ${CMAKE_CURRENT_LIST_DIR}")

cmake_minimum_required(VERSION 3.20.0)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_sources(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test_astar.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_bfs.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_dfs.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_heuristic0.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_manhattan_distance_1D.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_player_heuristic.cpp
            ${CMAKE_CURRENT_LIST_DIR}/test_random_walk.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Setup
            Solvers)
