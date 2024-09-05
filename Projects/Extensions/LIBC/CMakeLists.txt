INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

#ADD_SUBDIRECTORY(cassert)
#ADD_SUBDIRECTORY(cstring)


SET(SOURCES
	cassert/cassert.h
	cstring/strcat.h
	cstring/strchr.h
	cstring/strcmp.h
	cstring/strcoll.h
	cstring/strcspn.h
	cstring/strlen.h
	cstring/strncat.h
	cstring/strncmp.h
	cstring/strpbrk.h
	cstring/strspn.h
	cstring/strrchr.h
	cstring/strstr.h
	locale/setlocale.h
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
