INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

ADD_SUBDIRECTORY(Attributes)
ADD_SUBDIRECTORY(BuildInObjects)
#ADD_SUBDIRECTORY(Common)
ADD_SUBDIRECTORY(Designtime)
ADD_SUBDIRECTORY(Extensions)
#ADD_SUBDIRECTORY(Interfaces)
ADD_SUBDIRECTORY(Parser)
ADD_SUBDIRECTORY(Runtime)
ADD_SUBDIRECTORY(Utils)

SET(SOURCES
	Analyser.cpp
	Interpreter.cpp
	Memory.cpp
	Method.cpp
	Object.cpp
	Parameter.cpp
	Preprocessor.cpp
	Reference.cpp
	Repository.cpp
	Scope.cpp
	Script.cpp
	StackTrace.cpp
	Symbol.cpp
	Token.cpp
	Tokenizer.cpp
	Tools.cpp
	Types.cpp
	VirtualMachine.cpp
)

SET(HEADERS
	Analyser.h
	Consts.h
	Interpreter.h
	Memory.h
	Method.h
	Object.h
	ObjectiveScript.h
	Parameter.h
	Preprocessor.h
	Reference.h
	Repository.h
	Scope.h
	Script.h
	StackTrace.h
	Symbol.h
	Token.h
	Tokenizer.h
	Tools.h
	Types.h
	VirtualMachine.h
)

SET(DEPENDENCIES
	CoreUtils
	CoreRuntime
	CoreParser
	CoreExtensions
	CoreDebugger
	CoreDesigntimeBuildInTypes
	CoreDesigntime
	CoreBuildInObjects
	CoreAttributes
	Utils
)

add_include(Projects/Core)
add_include(Projects/Debugger)
add_include(Projects/Utils)

build_static_lib(Core "")

