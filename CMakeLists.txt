# minimum cmake version required
cmake_minimum_required(VERSION 3.13.4)

# project name
project("RUSH HOUR" LANGUAGES CXX)
message(STATUS "PROJECT NAME: " ${PROJECT_NAME})

set(VERSION_MAJOR BETA)
message(STATUS "VERSION: " ${VERSION_MAJOR})

# code language
message(STATUS "COMPILER: " ${CMAKE_CXX_COMPILER_ID})
function(check_cpp_version_support)
    # check for C++17 compiler support
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
    if (NOT COMPILER_SUPPORTS_CXX17)
        message(FATAL_ERROR 
                "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support.
                 Please use a different C++ compiler."
        )
    endif()
    set(CMAKE_CXX_STANDARD 17 PARENT_SCOPE)
    set(CMAKE_CXX_STANDARD_REQUIRED ON PARENT_SCOPE)
endfunction()

# set compile flags
macro(set_compiler_flags)
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE RELEASE)
    endif()
    message(STATUS "BUILD TYPE: " ${CMAKE_BUILD_TYPE})
    if(CMAKE_BUILD_TYPE MATCHES RELEASE)
        set(CMAKE_CXX_FLAGS "-std=c++17 -g -O2 -Wall -pthread")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
    elseif(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(GPP_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage -fno-exceptions")
        set(GPP_COVERAGE_LINK_FLAGS "-lgcov")
        set(CMAKE_CXX_FLAGS "-std=c++17 -g -O0 -Wall -pthread ${GPP_COVERAGE_LINK_FLAGS} ${GPP_COVERAGE_COMPILE_FLAGS}")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
    endif()
endmacro()

check_cpp_version_support() # check if compiler is supported
set_compiler_flags() # compiler options / flags

add_subdirectory(cppsrc)

add_subdirectory(cmddemo)