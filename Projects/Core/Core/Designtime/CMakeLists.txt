INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(BuildInTypes)
ADD_SUBDIRECTORY(Parser)

SET(SOURCES
	Ancestor.cpp
	BluePrintGeneric.cpp
	BluePrintEnum.cpp
	BluePrintObject.cpp
	Prototype.cpp
	SanityChecker.cpp
)

SET(HEADERS
	Ancestor.h
	BluePrintGeneric.h
	BluePrintEnum.h
	BluePrintObject.h
	Exceptions.h
	Prototype.h
	SanityChecker.h
)

SET(DEPENDENCIES
	CoreDesigntimeParser
	CoreDesigntimeBuildInTypes
	CoreAttributes
)

add_include(Projects/Core)

build_static_lib(CoreDesigntime "")
