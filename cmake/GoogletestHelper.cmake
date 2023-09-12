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
