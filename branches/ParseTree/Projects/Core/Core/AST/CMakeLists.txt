INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	TreeGenerator.cpp
	TreeVisitor.cpp
)

SET(HEADERS
	ControlStatements.h
	Expression.h
	Keywords.h
	Node.h
	Operator.h
	Statement.h
	TreeGenerator.h
	TreeVisitor.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreAST "")
