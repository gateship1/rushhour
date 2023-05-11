add_library(Setup STATIC)

target_sources(Setup
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/SetupDefaultBoard.cpp
            ${CMAKE_CURRENT_LIST_DIR}/SetupFromCmdLine.cpp
            ${CMAKE_CURRENT_LIST_DIR}/SetupFromFile.cpp
            ${CMAKE_CURRENT_LIST_DIR}/Setup.cpp)

target_include_directories(Setup
    PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(Setup PRIVATE GameEngine)

set_target_properties(Setup
    PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
