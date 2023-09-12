function(SET_DEFAULT_BUILD_TYPE)

    message(STATUS "No build type specified. No CMAKE_BUILD_TYPE cache variable used.")

    set(CMAKE_BUILD_TYPE
        ""
        CACHE STRING "Choose the type of build." FORCE
    )

    set_property(
        CACHE CMAKE_BUILD_TYPE
        PROPERTY STRINGS
            "Debug"
            "Release"
            "RelWithDebInfo"
            "MinSizeRel"
    )

endfunction(SET_DEFAULT_BUILD_TYPE)

function(SET_PROJECT_BUILD_TYPE)

    if(NOT CMAKE_BUILD_TYPE)
        set_default_build_type()
    else()
        message(STATUS "Setting build type to '${CMAKE_BUILD_TYPE}' as specified")
    endif()

endfunction(SET_PROJECT_BUILD_TYPE)

set_project_build_type()
