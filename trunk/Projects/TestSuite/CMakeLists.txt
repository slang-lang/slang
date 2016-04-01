INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(Inheritance)
ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Language)
ADD_SUBDIRECTORY(Math)
ADD_SUBDIRECTORY(Operator)
ADD_SUBDIRECTORY(Prototype)
ADD_SUBDIRECTORY(TestFramework)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	Utils
	Test_TestFramework
	Test_Prototype
	Test_Operator
	Test_Math
	Test_Language
	Test_Interfaces
	Test_Inheritance
	Test_Attributes
	Core
)

add_include(Projects/Core)
add_include(Projects/TestSuite)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/TestSuite)
build_app(TestSuite "")
