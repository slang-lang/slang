INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AffectedRows.cpp
	Close.cpp
	Connect.cpp
	ConnectionTest.cpp
	Error.cpp
	FieldCount.cpp
	FreeResult.cpp
	GetClientInfo.cpp
	GetFieldName.cpp
	GetFieldValue.cpp
	Info.cpp
	Init.cpp
	MysqlExtension.cpp
	NextResult.cpp
	NextRow.cpp
	NumFields.cpp
	NumRows.cpp
	Query.cpp
	MysqlRealEscapeString.cpp
	MysqlSelectDB.cpp
	StoreResult.cpp
	Types.cpp
	UseResult.cpp
)

SET(HEADERS
	AffectedRows.h
	Close.h
	Connect.h
	ConnectionTest.h
	Error.h
	FieldCount.h
	FreeResult.h
	GetClientInfo.h
	GetFieldName.h
	GetFieldValue.h
	Info.h
	Init.h
	MysqlExtension.h
	NextResult.h
	NextRow.h
	NumFields.h
	NumRows.h
	Query.h
	MysqlRealEscapeString.h
	MysqlSelectDB.h
	StoreResult.h
	Types.h
	UseResult.h
)

SET(DEPENDENCIES
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Extensions)
add_include(Projects/Utils)

build_static_lib(ExtensionsMysql "mysql")
