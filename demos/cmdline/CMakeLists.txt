#[=[ Rush Hour C++ source code for Terminal AI demo #]=]

add_executable(rush_hour_cmdline_demo ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

target_sources(rush_hour_cmdline_demo
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/CmdLineDemo.cpp)


target_include_directories(rush_hour_cmdline_demo 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
           ${CMAKE_SOURCE_DIR}/src/GameEngine
           ${CMAKE_SOURCE_DIR}/src/GameEngine/Vehicles
           ${CMAKE_SOURCE_DIR}/src/GameEngine/Vehicles/PhysicsEngine
           ${CMAKE_SOURCE_DIR}/src/Setup
           ${CMAKE_SOURCE_DIR}/src/Solvers)

target_link_libraries(rush_hour_cmdline_demo PUBLIC Game)

set_target_properties(rush_hour_cmdline_demo
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
