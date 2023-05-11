#[=[ Rush Hour C++ physics engine source code #]=]

add_library(PhysicsEngine STATIC)

target_sources(PhysicsEngine
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/collision_detected.cpp)

target_include_directories(PhysicsEngine 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR})

set_target_properties(PhysicsEngine
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
