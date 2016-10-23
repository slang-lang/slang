INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Controller.cpp
	Memory.cpp
	Repository.cpp
	Stack.cpp
	StackLevel.cpp
	VirtualMachine.cpp
	VirtualMethodTable.cpp
)

SET(HEADERS
	Controller.h
	Memory.h
	Repository.h
	Stack.h
	StackLevel.h
	VirtualMachine.h
	VirtualMethodTable.h
)

SET(DEPENDENCIES
	CoreBuildInObjects
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreVirtualMachine "")
