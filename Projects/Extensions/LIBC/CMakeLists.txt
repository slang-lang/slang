INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

#ADD_SUBDIRECTORY(cassert)
ADD_SUBDIRECTORY(cstring)
ADD_SUBDIRECTORY(fenv)
#ADD_SUBDIRECTORY(locale)
ADD_SUBDIRECTORY(math)
ADD_SUBDIRECTORY(stdio)
ADD_SUBDIRECTORY(stdlib)


SET(SOURCES
    locale/setlocale.h
    Extension.cpp
)

SET(HEADERS
    Extension.h
)

SET(DEPENDENCIES
    ExtensionsLIBCStdlib
    ExtensionsLIBCStdio
    ExtensionsLIBCMath
    ExtensionsLIBCFenv
    ExtensionsLIBCCstring
#    ExtensionsLIBCCassert
    CoreExtensions
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsLIBC "${MODULES}")
