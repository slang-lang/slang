INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	Fixture.cpp
	RealWorldUsageTest.cpp
)

SET(HEADERS
	Fixture.h
	RealWorldUsageTest.h
)

SET(DEPENDENCIES
	Core
)

add_include(Projects/Core)
add_include(Projects/TestSuite)
add_include(Projects/Utils)

build_static_lib(Test_RealWorldUsage "")

