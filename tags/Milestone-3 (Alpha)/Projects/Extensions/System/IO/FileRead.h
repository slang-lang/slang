
#ifndef ObjectiveScript_Extensions_System_IO_FileRead_h
#define ObjectiveScript_Extensions_System_IO_FileRead_h


// Library includes

// Project includes
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileReadBool : public ExtensionMethod
{
public:
	FileReadBool();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadDouble : public ExtensionMethod
{
public:
	FileReadDouble();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadFloat : public ExtensionMethod
{
public:
	FileReadFloat();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadInt : public ExtensionMethod
{
public:
	FileReadInt();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadString : public ExtensionMethod
{
public:
	FileReadString();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


}
}
}

#endif
