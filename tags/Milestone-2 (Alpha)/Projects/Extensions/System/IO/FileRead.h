
#ifndef ObjectiveScript_Extensions_System_IO_FileRead_h
#define ObjectiveScript_Extensions_System_IO_FileRead_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileReadBool : public Runtime::Method
{
public:
	FileReadBool();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadDouble : public Runtime::Method
{
public:
	FileReadDouble();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadFloat : public Runtime::Method
{
public:
	FileReadFloat();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadInt : public Runtime::Method
{
public:
	FileReadInt();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


class FileReadString : public Runtime::Method
{
public:
	FileReadString();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


}
}
}

#endif