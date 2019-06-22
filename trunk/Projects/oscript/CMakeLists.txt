INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

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
	mysql
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/oscript)
build_app(oscript "${MODULES}")

