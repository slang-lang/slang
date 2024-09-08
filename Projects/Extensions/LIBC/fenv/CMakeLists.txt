INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    fenv.cpp
)

SET(HEADERS
    fenv.hpp
)

SET(DEPENDENCIES
    Utils
    Core
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsLIBCFenv "${MODULES}")
