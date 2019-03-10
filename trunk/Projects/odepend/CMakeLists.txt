INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	main.cpp
	Module.cpp
	Repository.cpp
	Version.cpp
)

SET(HEADERS
	Defines.h
	Dependency.h
	Module.h
	Repository.h
	Version.h
)

SET(DEPENDENCIES
	Core
	Utils
)

add_include(Projects/Core)
add_include(Projects/odepend)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/odepend)
SET(MODULES curl json)
build_app(odepend "${MODULES}")

