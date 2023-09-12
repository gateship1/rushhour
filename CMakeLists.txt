cmake_minimum_required(VERSION 3.20.0)

project("RUSH HOUR"
    LANGUAGES CXX)

message(STATUS "PROJECT NAME: " ${PROJECT_NAME})

include(cmake/InternalHelpers.cmake)
include(cmake/PreventInSourceBuilds.cmake)
include(cmake/ProjectSettings.cmake)
include(cmake/ProjectGit.cmake)

add_subdirectory(src)

if (UNITTEST)
    enable_testing()
    include(cmake/GoogletestHelper.cmake)
    include(GoogleTest)
    add_subdirectory(test)
endif (UNITTEST)

if (DEMOS)
    add_subdirectory(demos)
endif (DEMOS)
