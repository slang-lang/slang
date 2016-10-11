
#ifndef ObjectiveScript_Extensions_System_IO_FileWrite_h
#define ObjectiveScript_Extensions_System_IO_FileWrite_h


// Library includes

// Project includes
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileWriteBool : public ExtensionMethod
{
public:
	FileWriteBool();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteDouble : public ExtensionMethod
{
public:
	FileWriteDouble();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteFloat : public ExtensionMethod
{
public:
	FileWriteFloat();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteInt : public ExtensionMethod
{
public:
	FileWriteInt();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteString : public ExtensionMethod
{
public:
	FileWriteString();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


}
}
}

#endif
