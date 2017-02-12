INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	ASTTest.cpp
	Fixture.cpp
)

SET(HEADERS
	ASTTest.h
	Fixture.h
)

SET(DEPENDENCIES
	Core
)

add_include(Projects/Core)
add_include(Projects/TestSuite)
add_include(Projects/Utils)

build_static_lib(Test_AST "")
