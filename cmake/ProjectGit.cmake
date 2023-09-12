find_package(Git)
if (NOT Git_FOUND)
    message(AUTHOR_WARNING "No git in ${binaries_path}, consider installing to enable features")
endif (NOT Git_FOUND)
