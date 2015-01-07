INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(Prototype)
ADD_SUBDIRECTORY(TestFramework)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	Test_TestFramework
	Test_Prototype
	Test_Attributes
	Utils
	Core
)

add_include(Projects/Core)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/TestSuite)
build_app(Test "")
