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
	MysqlNumFields.cpp
	MysqlPing.cpp
	MysqlQuery.cpp
	MysqlRealEscapeString.cpp
	MysqlSelectDB.cpp
	MysqlStoreResult.cpp
	MysqlUseResult.cpp
	NextResult.cpp
	NextRow.cpp
	NumRows.cpp
	Types.cpp
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
	MysqlNumFields.h
	MysqlPing.cpp
	MysqlQuery.h
	MysqlRealEscapeString.h
	MysqlSelectDB.h
	MysqlStat.h
	MysqlStoreResult.h
	MysqlUseResult.h
	NextResult.h
	NextRow.h
	NumRows.h
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
