INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Application)
ADD_SUBDIRECTORY(Common)

SET(SOURCES
    main.cpp
)

SET(HEADERS
)

SET(DEPENDENCIES
    SlangAppCommon
    SlangAppApplication
    ExtensionsLIBC
    ExtensionsSystem
    Core
    Utils
)

SET(MODULES
    curl
    json
)

add_include(Projects/Core)
add_include(Projects/slang-app)
add_include(Projects/Utils)

SET(EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/slang-app)
build_app(slang-app "${MODULES}")
