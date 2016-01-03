INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Configuration)

SET(SOURCES
	Context.cpp
	Logger.cpp
	StdOutLogger.cpp
)

SET(HEADERS
	Context.h
	Exceptions.h
	Logger.h
	StdOutLogger.h
)

SET(DEPENDENCIES
	UtilsTools
	UtilsCommonConfiguration
)

add_include(Projects/Utils)

build_static_lib(UtilsCommon "")
