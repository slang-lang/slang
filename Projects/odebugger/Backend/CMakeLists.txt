INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Backend.cpp
)

SET(HEADERS
	Backend.h
	IBackend.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/odebugger)
add_include(Projects/Utils)

build_static_lib(DebuggerBackend "")
