
#ifndef ObjectiveScript_Extensions_System_IO_FileSeek_h
#define ObjectiveScript_Extensions_System_IO_FileSeek_h


// Library includes

// Project includes
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileSeek : public ExtensionMethod
{
public:
	FileSeek();

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token);
};


}
}
}

#endif