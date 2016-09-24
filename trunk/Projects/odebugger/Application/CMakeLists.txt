INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Application.cpp
)

SET(HEADERS
    Application.h
)

SET(DEPENDENCIES
	DebuggerVSCodeRemoteClient
	DebuggerLocalClient
	CoreBuildInObjects
	Core
)

add_include(Projects/Core)
add_include(Projects/odebugger)
add_include(Projects/Utils)

build_static_lib(DebuggerApplication "")
