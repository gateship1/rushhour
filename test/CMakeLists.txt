define_test(TEST_NAME unittests
    TEST_DESCRIPTION "Unit test all functions"
    TEST_FILES ${CMAKE_CURRENT_LIST_DIR}/test_astar.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_bfs.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_collision_detected.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_dfs.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_driver.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_get_board_states.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_heuristic0.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_manhattan_distance_1D.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_is_solution_state.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_movement.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_next_boards.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_number_of_obstacles_1D.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_player_heuristic.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_print_board.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_random_walk.cpp
               ${CMAKE_CURRENT_LIST_DIR}/test_setup.cpp
               ${CMAKE_CURRENT_LIST_DIR}/UnitTest.cpp
    INCLUDE_DIRS $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/GameEngine>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/GameEngine/Vehicles>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/GameEngine/Vehicles/PhysicsEngine>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/Setup>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/Solvers>
                 $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test>
    LIBRARIES Game
              GameEngine
              PhysicsEngine
              Setup
              Solvers
              Vehicles
)
