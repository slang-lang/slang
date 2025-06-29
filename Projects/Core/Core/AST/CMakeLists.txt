INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Expression.cpp
	PrintVisitor.cpp
	TreeGenerator.cpp
	TreeInterpreter.cpp
	TreeLineBuffer.cpp
	TreeOptimizer.cpp
	TreeVisitor.cpp
)

SET(HEADERS
	Expression.h
	Node.h
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
	CoreDebugger
	CoreRuntime
	CoreCommon
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreAST "")
