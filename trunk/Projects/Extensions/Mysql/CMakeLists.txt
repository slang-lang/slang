INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	AffectedRows.cpp
	Connect.cpp
	Error.cpp
	FreeResult.cpp
	GetClientInfo.cpp
	GetFieldName.cpp
	GetFieldValue.cpp
	MysqlClose.cpp
	MysqlExtension.cpp
	MysqlFieldCount.cpp
	MysqlInfo.cpp
	MysqlInit.cpp
	MysqlPing.cpp
	MysqlRealEscapeString.cpp
	MysqlSelectDB.cpp
	NextResult.cpp
	NextRow.cpp
	NumFields.cpp
	NumRows.cpp
	Query.cpp
	StoreResult.cpp
	Types.cpp
	UseResult.cpp
)

SET(HEADERS
	AffectedRows.h
	Connect.h
	Error.h
	FreeResult.h
	GetClientInfo.h
	GetFieldName.h
	GetFieldValue.h
	MysqlClose.h
	MysqlDataSeek.h
	MysqlExtension.h
	MysqlFieldCount.h
	MysqlFieldSeek.h
	MysqlFieldTell.h
	MysqlInfo.h
	MysqlInit.h
	MysqlPing.cpp
	MysqlRealEscapeString.h
	MysqlSelectDB.h
	MysqlStat.h
	NextResult.h
	NextRow.h
	NumFields.h
	NumRows.h
	Query.h
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
