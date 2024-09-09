INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Console)
#ADD_SUBDIRECTORY(IO)
ADD_SUBDIRECTORY(Network)
ADD_SUBDIRECTORY(Reflection)
ADD_SUBDIRECTORY(Strings)
ADD_SUBDIRECTORY(Time)

SET(SOURCES
	System.cpp
	SystemExtension.cpp
)

SET(HEADERS
    System.h
	SystemExtension.h
)

SET(DEPENDENCIES
	ExtensionsSystemTime
	ExtensionsSystemStrings
	ExtensionsSystemReflection
	ExtensionsSystemNetwork
	ExtensionsSystemConsole
	CoreExtensions
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Extensions)

build_static_lib(ExtensionsSystem "${MODULES}")
