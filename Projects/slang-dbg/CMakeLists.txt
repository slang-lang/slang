INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Application)
ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(LocalClient)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(VSCodeRemoteClient)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	ExtensionsSystem
	ExtensionsJson
	DebuggerVSCodeRemoteClient
	DebuggerLocalClient
	DebuggerCommon
	DebuggerApplication
	CoreDebugger
	Core
	Utils
)

SET(MODULES
	json
)

add_include(Projects/Core)
add_include(Projects/slang-dbg)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/slang-dbg)
build_app(slang-dbg "${MODULES}")

