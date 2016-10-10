INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	StackLevel.cpp
	StackTrace.cpp
)

SET(HEADERS
	StackLevel.h
	StackTrace.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreVirtualMachine "")
