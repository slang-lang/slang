INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Application.cpp
)

SET(HEADERS
    Application.h
    Settings.h
)

SET(DEPENDENCIES
    ServerCommon
    Core
    UtilsLogger
    Utils
)

SET(MODULES
    json
    fcgi
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/slang-app)
add_include(Projects/Utils)

build_static_lib(ServerApplication "${MODULES}")
