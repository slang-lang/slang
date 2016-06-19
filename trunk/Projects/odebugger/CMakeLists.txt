INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Backend)
ADD_SUBDIRECTORY(LocalClient)
#ADD_SUBDIRECTORY(Interfaces)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	ExtensionsSystem
	ExtensionsMysql
	ExtensionsJson
	ExtensionsApache
	DebuggerLocalClient
	DebuggerBackend
	CoreDebugger
	Core
	Utils
)

add_include(Projects/Core)
add_include(Projects/odebugger)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/odebugger)
build_app(odebugger "mysql")
