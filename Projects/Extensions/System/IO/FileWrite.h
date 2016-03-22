
#ifndef ObjectiveScript_Extensions_System_IO_FileWrite_h
#define ObjectiveScript_Extensions_System_IO_FileWrite_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileWriteDouble : public Runtime::Method
{
public:
	FileWriteDouble();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};

class FileWriteFloat : public Runtime::Method
{
public:
	FileWriteFloat();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};

class FileWriteInt : public Runtime::Method
{
public:
	FileWriteInt();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};

class FileWriteString : public Runtime::Method
{
public:
	FileWriteString();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};


}
}
}

#endif
