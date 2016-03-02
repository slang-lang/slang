INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(BuildInTypes)

SET(SOURCES
		Ancestor.cpp
		BluePrint.cpp
		Prototype.cpp
		SanityChecker.cpp
)

SET(HEADERS
		Ancestor.h
		BluePrint.h
		Prototype.h
		SanityChecker.h
)

SET(DEPENDENCIES
	CoreDesigntimeBuildInTypes
	CoreAttributes
)

add_include(Projects/Core)

build_static_lib(CoreDesigntime "")
