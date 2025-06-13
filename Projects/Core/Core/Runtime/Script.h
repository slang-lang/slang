
#ifndef Slang_Core_Core_Runtime_Script_h
#define Slang_Core_Core_Runtime_Script_h


// Library includes

// Project includes
#include <Core/Common/Types.h>
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Runtime {
	class Object;
}
class Symbol;

class Script
{
public:
	Script() = default;
	~Script() = default;

public:	//Helpers
	Symbol* resolve(const std::string& symbol);
	Symbol* resolveMethod(const std::string& method, const ParameterList& params);

public:	// Execution
	void execute(ThreadId threadId, const std::string& method, const ParameterList& params, Runtime::Object* result);
};


}


#endif
