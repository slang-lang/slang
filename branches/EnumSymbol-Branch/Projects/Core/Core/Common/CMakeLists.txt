INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    StringTools.cpp
)

SET(HEADERS
    StringTools.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreCommon "")
