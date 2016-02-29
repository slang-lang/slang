INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(BuildInTypes)

SET(SOURCES
		Ancestor.cpp
		BluePrint.cpp
		Prototype.cpp
)

SET(HEADERS
		Ancestor.h
		BluePrint.h
		Prototype.h
)

SET(DEPENDENCIES
	CoreDesigntimeBuildInTypes
	CoreAttributes
)

add_include(Projects/Core)

build_static_lib(CoreDesigntime "")
