#[=[ Rush Hour C++ game / AI engine source code #]=]

# source list
set(ENGINE_SOURCE_CODE_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/astar.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bfs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/board.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/board.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dfs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/file_input.hpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/heuristics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/node.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/random_walk.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solution_path.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility_funcs.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vehicle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vehicle.hpp
)

# add source files to a library
add_library(rush_hour_cpp 
            STATIC
            ${ENGINE_SOURCE_CODE_LIST}
)

# set the library linker language
set_target_properties(rush_hour_cpp 
                      PROPERTIES 
                      LINKER_LANGUAGE CXX
)

# pass library
target_include_directories(rush_hour_cpp 
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR} 
)
target_link_libraries(rush_hour_cpp PUBLIC)
