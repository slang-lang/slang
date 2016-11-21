INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Exceptions.cpp
    Position.cpp
    PrototypeConstraint.cpp
    Visibility.cpp
)

SET(HEADERS
    Exceptions.h
    Position.h
    PrototypeConstraint.h
    TypeDeclaration.h
    Visibility.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)

build_static_lib(CoreCommon "")
