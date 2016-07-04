INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	MysqlAffectedRows.cpp
	MysqlClose.cpp
	MysqlConnect.cpp
	MysqlError.cpp
	MysqlExtension.cpp
	MysqlFieldCount.cpp
	MysqlFreeResult.cpp
	MysqlGetClientInfo.cpp
	MysqlGetFieldName.cpp
	MysqlGetFieldValue.cpp
	MysqlInfo.cpp
	MysqlInit.cpp
	MysqlNextResult.cpp
	MysqlNextRow.cpp
	MysqlNumFields.cpp
	MysqlNumRows.cpp
	MysqlPing.cpp
	MysqlQuery.cpp
	MysqlRealEscapeString.cpp
	MysqlSelectDB.cpp
	MysqlStoreResult.cpp
	MysqlUseResult.cpp
	Types.cpp
)

SET(HEADERS
	MysqlAffectedRows.h
	MysqlClose.h
	MysqlConnect.h
	MysqlDataSeek.h
	MysqlError.h
	MysqlExtension.h
	MysqlFieldCount.h
	MysqlFieldSeek.h
	MysqlFieldTell.h
	MysqlFreeResult.h
	MysqlGetClientInfo.h
	MysqlGetFieldName.h
	MysqlGetFieldValue.h
	MysqlInfo.h
	MysqlInit.h
	MysqlNextResult.h
	MysqlNextRow.h
	MysqlNumFields.h
	MysqlNumRows.h
	MysqlPing.cpp
	MysqlQuery.h
	MysqlRealEscapeString.h
	MysqlSelectDB.h
	MysqlStat.h
	MysqlStoreResult.h
	MysqlUseResult.h
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
