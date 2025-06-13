INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Configuration)

SET(SOURCES
)

SET(HEADERS
	Exceptions.h
)

SET(DEPENDENCIES
	UtilsCommonConfiguration
)

add_include(Projects/Utils)

build_static_lib(UtilsCommon "")
