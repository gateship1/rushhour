# minimum cmake version required
cmake_minimum_required(VERSION 3.20.0)

# project name
project("RUSH HOUR" LANGUAGES CXX)
message(STATUS "PROJECT NAME: " ${PROJECT_NAME})

add_subdirectory(src)

add_subdirectory(demos)
