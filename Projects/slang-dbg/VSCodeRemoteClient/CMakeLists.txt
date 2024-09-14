INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Protocol.cpp
	RemoteClient.cpp
)

SET(HEADERS
	Protocol.h
	RemoteClient.h
)

SET(DEPENDENCIES
	ExtensionsSystem
	DebuggerCommon
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/slang-dbg)
add_include(Projects/Utils)

build_static_lib(DebuggerVSCodeRemoteClient "json")

