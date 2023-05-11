#[=[ Rush Hour C++ solver engine source code #]=]

add_library(Solvers STATIC)

target_sources(Solvers
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/AStar.cpp
            ${CMAKE_CURRENT_LIST_DIR}/BFS.cpp
            ${CMAKE_CURRENT_LIST_DIR}/DFS.cpp
            ${CMAKE_CURRENT_LIST_DIR}/heuristics.cpp
            ${CMAKE_CURRENT_LIST_DIR}/RandomWalk.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Solver.cpp)

target_include_directories(Solvers 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Solvers PRIVATE GameEngine)

set_target_properties(Solvers
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
