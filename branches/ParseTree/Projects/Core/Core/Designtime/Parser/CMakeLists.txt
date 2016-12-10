INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Parser.cpp
	Token.cpp
	Tokenizer.cpp
)

SET(HEADERS
	Parser.h
	Token.h
	Tokenizer.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreDesigntimeParser "")
