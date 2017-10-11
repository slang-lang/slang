INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Generator.cpp
	NodeFactory.cpp
	NodeIdentifier.cpp
	PrintVisitor.cpp
	TreeGenerator.cpp
	TreeInterpreter.cpp
	TreeLineBuffer.cpp
	TreeOptimizer.cpp
	TreeVisitor.cpp
)

SET(HEADERS
	ControlStatements.h
	Expression.h
	Generator.h
	Keywords.h
	Node.h
	NodeFactory.h
	NodeIdentifier.h
	Operator.h
    PrintVisitor.h
	Statement.h
	TreeGenerator.h
	TreeInterpreter.h
	TreeLineBuffer.h
	TreeOptimizer.h
	TreeVisitor.h
)

SET(DEPENDENCIES
	CoreRuntime
	CoreCommon
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreAST "")
