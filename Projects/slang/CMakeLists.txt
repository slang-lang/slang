INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	ExtensionsLIBC
	ExtensionsSystem
	DebuggerVSCodeRemoteClient
	DebuggerLocalClient
	DebuggerCommon
	DebuggerApplication
	CoreDebugger
	Core
	UtilsLogger
	Utils
)

SET(MODULES
	json
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/slang)
build_app(slang "${MODULES}")

