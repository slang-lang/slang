INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AffectedRows.cpp
	Close.cpp
	Connect.cpp
	ConnectionTest.cpp
	Error.cpp
	FreeResult.cpp
	GetClientInfo.cpp
	Info.cpp
	Init.cpp
	MysqlExtension.cpp
	NumRows.cpp
	Query.cpp
	StoreResult.cpp
	Types.cpp
)

SET(HEADERS
	AffectedRows.h
	Close.h
	Connect.h
	ConnectionTest.h
	Error.h
	FreeResult.h
	GetClientInfo.h
	Info.h
	Init.h
	MysqlExtension.h
	NumRows.h
	Query.h
	StoreResult.h
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
