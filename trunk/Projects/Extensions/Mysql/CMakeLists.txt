INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Close.cpp
	Connect.cpp
	ConnectionTest.cpp
	GetClientInfo.cpp
	Info.cpp
	Init.cpp
	MysqlExtension.cpp
	Types.cpp
)

SET(HEADERS
	Close.h
	Connect.h
	ConnectionTest.h
	GetClientInfo.h
	Info.h
	Init.h
	MysqlExtension.h
	Types.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsMysql "mysql")
