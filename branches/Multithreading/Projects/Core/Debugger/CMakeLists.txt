INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BreakPoint.cpp
	Condition.cpp
	Debugger.cpp
)

SET(HEADERS
	BreakPoint.h
	Condition.h
	Debugger.h
	IDebugger.h
	IReceiver.h
)

SET(DEPENDENCIES
	CoreVirtualMachine
	CoreRuntime
	Core
)

SET(MODULES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreDebugger "${MODULES}")
