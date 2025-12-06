INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Service.cpp
)

SET(HEADERS
    Consts.h
    Defines.h
    Service.h
)

SET(DEPENDENCIES
    Core
    Utils
)

add_include(Projects/Core)
add_include(Projects/slang-app)
add_include(Projects/Utils)

build_static_lib(SlangAppCommon "json")
