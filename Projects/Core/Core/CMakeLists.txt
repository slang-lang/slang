INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(BuildInObjects)
ADD_SUBDIRECTORY(Helpers)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Utils)

SET(SOURCES
	Analyser.cpp
	BluePrint.cpp
	Interface.cpp
#	Interpreter.cpp
	Memory.cpp
	Method.cpp
	Object.cpp
	OperatorOverloading.cpp
	Parameter.cpp
	Preprocessor.cpp
	Prototype.cpp
	Reference.cpp
	Repository.cpp
	Scope.cpp
	Script.cpp
	Stack.cpp
	System.cpp
	Token.cpp
	Tokenizer.cpp
	Tools.cpp
	Types.cpp
	Variable.cpp
	VirtualMachine.cpp
)

SET(HEADERS
	Analyser.h
	BluePrint.h
	Consts.h
	Interface.h
#	Interpreter.h
	Memory.h
	Method.h
	Object.h
#	ObjectiveScript.h
	OperatorOverloading.h
	Parameter.h
	Preprocessor.h
	Prototype.h
	Reference.h
	Repository.h
	RTTI.h
	Scope.h
	Script.h
	Stack.h
	System.h
	Symbol.h
	Token.h
	Tokenizer.h
	Tools.h
	Types.h
	Variable.h
	VirtualMachine.h
)

SET(DEPENDENCIES
	CoreUtils
	CoreHelpers
	CoreBuildInObjects
	CoreAttributes
	Utils
)

add_include(Projects/Core)
add_include(Projects/Utils)

build_static_lib(Core "")
