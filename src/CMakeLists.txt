#[=[ Rush Hour C++ game / AI engine source code #]=]

add_library(rush_hour_engine STATIC)

target_sources(rush_hour_engine
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/board.cpp
            ${CMAKE_CURRENT_LIST_DIR}/file_input.cpp
            ${CMAKE_CURRENT_LIST_DIR}/game.cpp
            ${CMAKE_CURRENT_LIST_DIR}/vehicle.cpp)

target_include_directories(rush_hour_engine 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(rush_hour_engine
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
