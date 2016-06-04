
function(build_static_testlib target modules)

    LIST(LENGTH HEADERS num_headers)
    if ( num_headers GREATER 0 )
        # modify given headers
        qt_wrap_cpp(${target} HEADERS ${HEADERS})
    endif()

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


function(build_test_app target modules)

    SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/testbin")
    LIST(APPEND DEPENDENCIES Utils UtilsTestManagement)
    LIST(APPEND modules "qttest")

    build_app(${target} "${modules}")

endfunction()


function(build_qtgui_app target modules)

    LIST(LENGTH FORMS num_forms)
    if ( num_forms GREATER 0 )
        qt4_wrap_ui(HEADERS ${FORMS})
        # the generated .h files are in the binary dir
        include_directories(${CMAKE_CURRENT_BINARY_DIR})
    endif()

    LIST(APPEND modules "qtgui")

    MESSAGE(FATAL_ERROR "${target} ${modules}")

    build_app(${target} "${modules}")

endfunction()


function(build_app target modules)

    _handle_modules_pre_linker("${modules}")

    SET(CMAKE_CXX_FLAGS "-Wl,--as-needed")
    LIST(LENGTH HEADERS num_headers)
    #if ( num_headers GREATER 0 )
    #    qt_wrap_cpp(${target} HEADERS ${HEADERS})
    #endif()

    add_executable(${target} ${SOURCES} ${HEADERS})

    # link against specified libs
    target_link_libraries(${target} ${DEPENDENCIES})

    _handle_modules_post_linker("${modules}" ${target})

endfunction()


function(_handle_modules_pre_linker modules)

    # make qt available to all by default
    #_handle_pre_qtcore()

    #list(FIND modules "qtgui" found)
    #if ( ${found} GREATER -1 )
    #    _handle_pre_qtgui()
    #endif()

    #list(FIND modules "qtsql" found)
    #if ( ${found} GREATER -1 )
    #    _handle_pre_qtsql()
    #endif()

    #list(FIND modules "qttest" found)
    #if ( ${found} GREATER -1 )
    #    _handle_pre_qttest()
    #endif()

    list(FIND modules "boost" found)
    if ( ${found} GREATER -1 )
        _handle_pre_boost()
    endif()

    #list(FIND modules "json" found)
    #if ( ${found} GREATER -1 )
        _handle_pre_json()
    #endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_pre_mysql()
    endif()

endfunction()


function(_handle_modules_post_linker modules target)

    # link against qtcore by default 
    #_handle_post_qtcore(${target})

    #list(FIND modules "qtgui" found)
    #if ( ${found} GREATER -1 )
    #    _handle_post_qtgui(${target})
    #endif()

    #list(FIND modules "qtsql" found)
    #if ( ${found} GREATER -1 )
    #    _handle_post_qtsql(${target})
    #endif()

    #list(FIND modules "qttest" found)
    #if ( ${found} GREATER -1 )
    #    _handle_post_qttest(${target})
    #endif()

    #list(FIND modules "json" found)
    #if ( ${found} GREATER -1 )
        _handle_post_json(${target})
    #endif()

    list(FIND modules "mysql" found)
    if ( ${found} GREATER -1 )
        _handle_post_mysql(${target})
    endif()

endfunction()


function(_handle_pre_boost)

    # make sure the appropriate environment variable is set!
    if("${BUILD_BOOST_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_BOOST_INC needed for boost!")
    endif()

    include_directories(${BUILD_BOOST_INC})

endfunction()


function(_json_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_JSON_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_JSON_INC needed for json!")
    endif()

    if("${BUILD_JSON_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_JSON_LIB needed for json!")
    endif()

endfunction()


function(_handle_pre_json)

    _json_check_existence()
    include_directories(${BUILD_JSON_INC})
    link_directories(${BUILD_JSON_LIB})

endfunction()


function(_handle_post_json target)

    _json_check_existence()
    target_link_libraries(${target} Json)

endfunction()


function(_mysql_check_existence)

    # make sure the appropriate environment variable is set!
    if("${BUILD_MYSQL_INC}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_INC needed for mysql!")
    endif()

    if("${BUILD_MYSQL_LIB}" STREQUAL "")
        MESSAGE(FATAL_ERROR "BUILD_MYSQL_LIB needed for mysql!")
    endif()

endfunction()


function(_handle_pre_mysql)

    _mysql_check_existence()
    include_directories(${BUILD_MYSQL_INC})
    link_directories(${BUILD_MYSQL_LIB})

endfunction()


function(_handle_post_mysql target)

    _mysql_check_existence()
    target_link_libraries(${target} mysqlclient)

endfunction()


function(_handle_pre_qtcore)

        find_package(Qt4)
        SET(QT_DONT_USE_QTGUI 1)
        include(${QT_USE_FILE})

endfunction()


function(_handle_post_qtcore target)

    target_link_libraries(${target} ${QT_LIBRARIES} ${QT_QTCORE_LIBRARY})

endfunction()


function(_handle_pre_qtgui)

        find_package(Qt4 COMPONENTS QtGui REQUIRED)
        SET(QT_USE_QTGUI 1)
        SET(QT_DONT_USE_QTGUI 0)
        include(${QT_USE_FILE})

endfunction()


function(_handle_post_qtgui target)

    target_link_libraries(${target} ${QT_QTGUI_LIBRARY})

endfunction()


function(_handle_pre_qtsql)

        find_package(Qt4 COMPONENTS QtSql REQUIRED)
        SET(QT_DONT_USE_QTGUI 1)
        SET(QT_USE_QTSQL 1)
        include(${QT_USE_FILE})

endfunction()


function(_handle_post_qtsql target)

    target_link_libraries(${target} ${QT_QTSQL_LIBRARY})

endfunction()


function(_handle_pre_qttest)

        find_package(Qt4 COMPONENTS QtSql REQUIRED)
        SET(QT_DONT_USE_QTGUI 1)
        SET(QT_USE_QTSQL 1)
        include(${QT_USE_FILE})

endfunction()


function(_handle_post_qttest target)

    target_link_libraries(${target} ${QT_QTTEST_LIBRARY})

endfunction()
