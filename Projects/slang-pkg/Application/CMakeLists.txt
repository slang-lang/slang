INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Application.cpp
)

SET(HEADERS
    Application.h
    Settings.h
)

SET(DEPENDENCIES
    PackageCommon
    Core
    UtilsLogger
    Utils
)

add_include(Projects/Core)
add_include(Projects/slang-pkg)
add_include(Projects/Utils)

build_static_lib(PackageApplication "json")
