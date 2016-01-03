INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ConfigParser.cpp
	Evaluator.cpp
	LineParser.cpp
	Tokenizer.cpp
	Value.cpp
	Valueizer.cpp
)

SET(HEADERS
	ConfigParser.h
	Evaluator.h
	LineParser.h
	Tokenizer.h
	Value.h
	Valueizer.h
)

SET(DEPENDENCIES )

add_include(Projects/Utils)

build_static_lib(UtilsParsers "")
