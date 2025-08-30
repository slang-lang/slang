INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)

SET(SOURCES
    Exceptions.cpp
    Method.cpp
    Namespace.cpp
	Parameter.cpp
    Position.cpp
    PrototypeConstraint.cpp
    Token.cpp
    Types.cpp
    Visibility.cpp
    Utils.cpp
)

SET(HEADERS
    Exceptions.h
    Method.h
    Namespace.h
	Parameter.h
    Position.h
    PrototypeConstraint.h
    Token.h
    TypeDeclaration.h
    Types.h
    Visibility.h
    Utils.h
)

SET(DEPENDENCIES
    CoreCommonAttributes
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(CoreCommon "")
