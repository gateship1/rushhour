find_package(GTest)
if (NOT GTest_FOUND)

    message(STATUS "Cloning google test...")

    include(FetchContent)
    
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
    )
    
    FetchContent_GetProperties(googletest)
    if(NOT googletest_POPULATED)
        FetchContent_Populate(googletest)
        add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
    endif(NOT googletest_POPULATED)

endif (NOT GTest_FOUND)
    
message(STATUS "googletest source directory: ${googletest_SOURCE_DIR}")
message(STATUS "googletest binary directory: ${googletest_BINARY_DIR}")


function(define_test)

    set(prefix ARGS)
    set(single_value_args TEST_NAME TEST_DESCRIPTION)
    set(multi_value_args SRC_FILES TEST_FILES INCLUDE_DIRS LIBRARIES)
    cmake_parse_arguments(
        PARSE_ARGV 0 ${prefix}
        "" "${single_value_args}" "${multi_value_args}"
    )
    error_for_unparsed(ARGS)

    add_executable(${ARGS_TEST_NAME} ${ARGS_TEST_FILES} ${ARGS_SRC_FILES})

    target_include_directories(${ARGS_TEST_NAME} 
        PRIVATE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
                $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test>
                $<BUILD_INTERFACE:${ARGS_INCLUDE_DIRS}>
    )

    target_link_libraries(${ARGS_TEST_NAME}
        PRIVATE gtest_main
                ${ARGS_LIBRARIES}
    )

    if (UNIX)
        target_link_libraries(${ARGS_TEST_NAME}
            PRIVATE gcov
        )
    endif (UNIX)

    add_test(NAME ${ARGS_TEST_DESCRIPTION} COMMAND ${ARGS_TEST_NAME})

endfunction()
