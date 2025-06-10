INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Application)
ADD_SUBDIRECTORY(Common)

SET(SOURCES
	main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
	PackageCommon
	PackageApplication
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
