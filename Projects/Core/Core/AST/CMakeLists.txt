INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Generator.cpp
	TreeGenerator.cpp
	TreeInterpreter.cpp
	TreeVisitor.cpp
)

SET(HEADERS
	ControlStatements.h
	Expression.h
	Generator.h
	Keywords.h
	Node.h
	Operator.h
	Statement.h
	TreeGenerator.h
	TreeInterpreter.h
	TreeVisitor.h
)

SET(DEPENDENCIES
	CoreCommon
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreAST "")
