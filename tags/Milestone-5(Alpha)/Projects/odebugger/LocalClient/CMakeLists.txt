INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	LocalClient.cpp
	Watch.cpp
)

SET(HEADERS
	LocalClient.h
	Watch.h
)

SET(DEPENDENCIES
	ExtensionsSystem
#	ExtensionsMysql
	ExtensionsJson
#	ExtensionsApache
	DebuggerCommon
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/odebugger)
add_include(Projects/Utils)

build_static_lib(DebuggerLocalClient "json")
