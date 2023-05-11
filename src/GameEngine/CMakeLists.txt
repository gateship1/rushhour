#[=[ Rush Hour C++ game engine source code #]=]

add_library(GameEngine STATIC)

add_subdirectory(Vehicles)

target_sources(GameEngine
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Board.cpp)

target_include_directories(GameEngine 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
           ${CMAKE_CURRENT_LIST_DIR}/Vehicles
           ${CMAKE_CURRENT_LIST_DIR}/Vehicles/PhysicsEngine)

target_link_libraries(GameEngine
    PUBLIC Vehicles)

set_target_properties(GameEngine
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
