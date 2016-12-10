INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	TreeGenerator.cpp
)

SET(HEADERS
	BinaryOperator.h
	Expression.h
	Node.h
	Operator.h
	Statement.h
	TreeGenerator.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreAST "")
