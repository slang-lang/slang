INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Context.cpp
    FileLogger.cpp
    Logger.cpp
    StackTrace.cpp
    StdOutLogger.cpp
)

SET(HEADERS
    Context.h
    FileLogger.h
    Logger.h
    StackTrace.h
    StdOutLogger.h
)

SET(DEPENDENCIES
    UtilsCommon
)

add_include(Projects/Utils)

build_static_lib(UtilsLogger "")
