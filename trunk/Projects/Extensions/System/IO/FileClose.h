
#ifndef ObjectiveScript_Extensions_System_IO_FileClose_h
#define ObjectiveScript_Extensions_System_IO_FileClose_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileClose : public Runtime::Method
{
public:
	FileClose();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};


}
}
}

#endif
