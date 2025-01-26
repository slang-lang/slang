INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(MyUnit)
ADD_SUBDIRECTORY(Parsers)
ADD_SUBDIRECTORY(SemVer)
ADD_SUBDIRECTORY(Tools)

SET(SOURCES
	Utils.cpp
)

SET(HEADERS
	Utils.h
)

SET(DEPENDENCIES
	UtilsTools
	UtilsSemVer
	UtilsParsers
	UtilsMyUnit
	UtilsCommonConfiguration
	UtilsCommon
)

build_static_lib( Utils "" )
