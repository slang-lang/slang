INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Exceptions.cpp
    Method.cpp
    Namespace.cpp
    Position.cpp
    PrototypeConstraint.cpp
    Types.cpp
    Visibility.cpp
)

SET(HEADERS
    Exceptions.h
    Method.h
    Namespace.h
    Position.h
    PrototypeConstraint.h
    TypeDeclaration.h
    Types.h
    Visibility.h
)

SET(DEPENDENCIES
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreCommon "")
