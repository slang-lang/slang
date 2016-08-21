
#ifndef ObjectiveScript_Extensions_System_IO_FileWrite_h
#define ObjectiveScript_Extensions_System_IO_FileWrite_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileWriteBool : public Runtime::Method
{
public:
	FileWriteBool();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteDouble : public Runtime::Method
{
public:
	FileWriteDouble();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteFloat : public Runtime::Method
{
public:
	FileWriteFloat();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteInt : public Runtime::Method
{
public:
	FileWriteInt();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileWriteString : public Runtime::Method
{
public:
	FileWriteString();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


}
}
}

#endif
