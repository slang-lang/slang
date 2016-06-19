INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	LocalClient.cpp
	Settings.h
)

SET(HEADERS
	LocalClient.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/odebugger)
add_include(Projects/Utils)

build_static_lib(DebuggerLocalClient "")
