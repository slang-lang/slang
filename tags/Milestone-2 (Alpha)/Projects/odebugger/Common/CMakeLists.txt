INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AClient.cpp
)

SET(HEADERS
	AClient.h
	Settings.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/odebugger)
add_include(Projects/Utils)

build_static_lib(DebuggerCommon "")
