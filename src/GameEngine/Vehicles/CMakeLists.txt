#[=[ Rush Hour C++ vehicles source code #]=]

add_subdirectory(PhysicsEngine)

add_library(Vehicles STATIC)

target_sources(Vehicles
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/HorizontalVehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/PlayerVehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Vehicle.cpp
            ${CMAKE_CURRENT_LIST_DIR}/VerticalVehicle.cpp)

target_include_directories(Vehicles
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
           ${CMAKE_CURRENT_LIST_DIR}/PhysicsEngine)

target_link_libraries(Vehicles PUBLIC PhysicsEngine)

set_target_properties(Vehicles
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
