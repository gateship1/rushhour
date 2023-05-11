function(error_for_unparsed PREFIX)
    set(ARGS "${${PREFIX}_UNPARSED_ARGUMENTS}")
    if (NOT ( "${ARGS}" STREQUAL ""))
        message(FATAL_ERROR "unparsed argument: ${ARGS}")
    endif ()
endfunction(error_for_unparsed)


function(parse_function_arguments)
    set(prefix ARGS)
    set(single_value_args TARGET)
    set(multi_values_args SRCS HDRS)
    cmake_parse_arguments(
        PARSE_ARGV 0
        ${prefix} "" "${single_values_args}" "${multi_values_args}"
    )
endfunction(parse_function_arguments)
