#[=[ Rush Hour C++ source code for Terminal AI demo #]=]

# source list
set(DEMO_SOURCE_CODE_LIST 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/run_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/run_demo.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threadstopper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/threadstopper.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheeltask.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/wheeltask.hpp
)

# build executable
add_executable(rush_hour.x ${DEMO_SOURCE_CODE_LIST})
target_link_libraries(rush_hour.x PUBLIC rush_hour_cpp)