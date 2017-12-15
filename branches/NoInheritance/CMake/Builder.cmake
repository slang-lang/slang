
function(build_static_testlib target modules)

    # append our utils testmanagement
    list(APPEND DEPENDENCIES "UtilsTestManagement")

    build_static_lib(${target} "${modules}")

endfunction()


function(build_static_lib target modules)

    _handle_modules_pre_linker("${modules}")

    add_library(${target} ${SOURCES} ${HEADERS})

    LIST(LENGTH DEPENDENCIES num_dependencies)
    if ( num_dependencies GREATER 0 )
        target_link_libraries(${target} ${DEPENDENCIES})
    endif()

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(build_app target modules)

    _handle_modules_pre_linker("${modules}")

    SET(CMAKE_CXX_FLAGS "-Wl,--as-needed")
    LIST(LENGTH HEADERS num_headers)

    add_executable(${target} ${SOURCES} ${HEADERS})

    # link against specified libs
    target_link_libraries(${target} ${DEPENDENCIES})

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(_handle_modules_pre_linker modules)

    list(FIND modules "boost" found)
    if ( ${found} GREATER -1 )
        _handle_pre_boost()
    endif()

    list(FIND modules "curl" found)
    if ( ${found} GREATER -1 )
        _handle_pre_curl()
    endif()

    list(FIND modules "json" found)
    if ( ${found} GREATER -1 )
        _handle_pre_json()
    endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_pre_mysql()
    endif()

endfunction()


function(_handle_modules_post_linker modules target)

    list(FIND modules "boost" found)
    if ( ${found} GREATER -1 )
        _handle_post_boost(${target})
    endif()

    list(FIND modules "curl" found)
    if ( ${found} GREATER -1 )
        _handle_post_curl(${target})
    endif()

    list(FIND modules "json" found)
    if ( ${found} GREATER -1 )
        _handle_post_json(${target})
    endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_post_mysql(${target})
    endif()

endfunction()


###############################
### BOOST

function(_boost_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_BOOST_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_BOOST_INC needed for boost!")
    endif()

endfunction()


function(_handle_post_boost)

endfunction()


function(_handle_pre_boost)

    _boost_check_existance()
    include_directories(${BUILD_BOOST_INC})

endfunction()

### BOOST
###############################

###############################
### CURL

function(_curl_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_CURL_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_CURL_INC needed for curl!")
    endif()
    if("${BUILD_CURL_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_CURL_LIB needed for curl!")
    endif()

endfunction()

function(_handle_post_curl target)

    _curl_check_existence()
    target_link_libraries(${target} curl)

endfunction()

function(_handle_pre_curl)

    _curl_check_existence()
    include_directories(${BUILD_CURL_INC})

endfunction()

### CURL
###############################

###############################
### JSON

function(_json_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_JSON_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_JSON_INC needed for json!")
    endif()

    if("${BUILD_JSON_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_JSON_LIB needed for json!")
    endif()

endfunction()

function(_handle_post_json target)

    _json_check_existence()
    target_link_libraries(${target} Json)

endfunction()

function(_handle_pre_json)

    _json_check_existence()
    include_directories(${BUILD_JSON_INC})
    link_directories(${BUILD_JSON_LIB})

endfunction()

### JSON
###############################

###############################
### MYSQL

function(_mysql_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_MYSQL_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_INC needed for mysql!")
    endif()

    if("${BUILD_MYSQL_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_LIB needed for mysql!")
    endif()

endfunction()

function(_handle_post_mysql target)

    _mysql_check_existence()
    target_link_libraries(${target} mysqlclient)

endfunction()

function(_handle_pre_mysql)

    _mysql_check_existence()
    include_directories(${BUILD_MYSQL_INC})
    link_directories(${BUILD_MYSQL_LIB})

endfunction()

### MYSQL
###############################

