INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ExtensionManager.cpp
)

SET(HEADERS
	AExtension.h
	ExtensionManager.h
	ExtensionMethod.h
	ExtensionNamespace.h
)

SET(DEPENDENCIES
	dl
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreExtensions "")
