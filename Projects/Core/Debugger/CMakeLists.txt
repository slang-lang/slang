INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	BreakPoint.cpp
	Debugger.cpp
)

SET(HEADERS
	BreakPoint.h
	Debugger.h
	IDebugger.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreDebugger "")
