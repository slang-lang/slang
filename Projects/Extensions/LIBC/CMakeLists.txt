INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

#ADD_SUBDIRECTORY(cassert)
#ADD_SUBDIRECTORY(cstring)


SET(SOURCES
	cassert/cassert.h
	cstring/strcat.h
	cstring/strlen.h
	cstring/strncat.h
	cstring/strncmp.h
	Extension.cpp
)

SET(HEADERS
	Extension.h
)

SET(DEPENDENCIES
	CoreExtensions
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsLIBC "${MODULES}")
