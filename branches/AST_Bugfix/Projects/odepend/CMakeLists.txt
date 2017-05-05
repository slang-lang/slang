INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	main.cpp
	Module.cpp
	Repository.cpp
)

SET(HEADERS
	Module.h
	Repository.h
)

SET(DEPENDENCIES
	Core
	Utils
)

add_include(Projects/Core)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/odepend)
build_app(odepend "curl")

