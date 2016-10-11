INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AExtension.cpp
)

SET(HEADERS
	AExtension.h
	ExtensionMethod.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreExtensions "")
