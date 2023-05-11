#[=[ Rush Hour source code #]=]

add_subdirectory(GameEngine)
add_subdirectory(Setup)
add_subdirectory(Solvers)

add_library(Game STATIC)

target_sources(Game
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Game.cpp)

target_include_directories(Game 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Game
    PUBLIC GameEngine
           Setup
           Solvers)

set_target_properties(Game
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
