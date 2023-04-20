#[=[ Rush Hour C++ source code for Terminal AI demo #]=]

add_executable(rush_hour_cmdline_demo ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

target_sources(rush_hour_cmdline_demo
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/run_demo.cpp
            ${CMAKE_CURRENT_LIST_DIR}/threadstopper.cpp
            ${CMAKE_CURRENT_LIST_DIR}/wheeltask.cpp)


target_include_directories(rush_hour_cmdline_demo 
    PUBLIC ${CMAKE_SOURCE_DIR}/src
           ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(rush_hour_cmdline_demo PUBLIC rush_hour_engine)

set_target_properties(rush_hour_cmdline_demo
    PROPERTIES LINKER_LANGUAGE CXX
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
