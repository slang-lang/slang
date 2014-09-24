INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
)

SET(HEADERS
	AKeyword.h
	for.h
	if.h
	print.h
	return.h
)

SET(DEPENDENCIES
)

build_static_lib(CoreKeywords "")

