
#ifndef ObjectiveScript_Extensions_System_IO_FileOpen_h
#define ObjectiveScript_Extensions_System_IO_FileOpen_h


// Library includes

// Project includes
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileOpen : public Runtime::Method
{
public:
	FileOpen();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);

private:
	int parseAccessMode(std::string accessmode) const;
};


}
}
}

#endif
