INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Controller.cpp
	Memory.cpp
	Repository.cpp
	StackLevel.cpp
	StackTrace.cpp
	VirtualMachine.cpp
)

SET(HEADERS
	Controller.h
	Memory.h
	Repository.h
	StackLevel.h
	StackTrace.h
	VirtualMachine.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreVirtualMachine "")
