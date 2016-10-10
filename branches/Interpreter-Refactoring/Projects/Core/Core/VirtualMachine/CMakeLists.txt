INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Memory.cpp
	Repository.cpp
	StackLevel.cpp
	StackTrace.cpp
)

SET(HEADERS
	Memory.h
	Repository.h
	StackLevel.h
	StackTrace.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreVirtualMachine "")
