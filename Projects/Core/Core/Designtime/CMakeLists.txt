INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(BuildInTypes)
ADD_SUBDIRECTORY(Parser)

SET(SOURCES
	Analyser.cpp
	Ancestor.cpp
	BluePrintObject.cpp
	SanityChecker.cpp
)

SET(HEADERS
	Analyser.h
	Ancestor.h
	BluePrintObject.h
	Exceptions.h
	SanityChecker.h
)

SET(DEPENDENCIES
	CoreDesigntimeParser
	CoreDesigntimeBuildInTypes
	CoreCommon
	CoreCommonAttributes
	CoreAST
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreDesigntime "")
