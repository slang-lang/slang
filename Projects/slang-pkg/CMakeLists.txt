INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
	main.cpp
	Module.cpp
	Repository.cpp
)

SET(HEADERS
	Consts.h
	Defines.h
	Dependency.h
	Module.h
	Repository.h
	Restriction.h
)

SET(DEPENDENCIES
	Core
	Utils
)

SET(MODULES
	curl
	json
)

add_include(Projects/Core)
add_include(Projects/slang-pkg)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/slang-pkg)
build_app(slang-pkg "${MODULES}")
