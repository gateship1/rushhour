function(ERROR_FOR_UNPARSED PREFIX)

    set(ARGS "${${PREFIX}_UNPARSED_ARGUMENTS}")

    if(NOT ( "${ARGS}" STREQUAL ""))
        message(FATAL_ERROR "unparsed argument: ${ARGS}")
    endif()

endfunction(ERROR_FOR_UNPARSED)

function(PARSE_FUNCTION_ARGUMENTS)

    set(prefix ARGS)
    set(single_value_args TARGET)
    set(multi_value_args SRCS HDRS)

    cmake_parse_arguments(
        PARSE_ARGV 0
        ${prefix} "" "${single_values_args}" "${multi_values_args}"
    )

endfunction(PARSE_FUNCTION_ARGUMENTS)