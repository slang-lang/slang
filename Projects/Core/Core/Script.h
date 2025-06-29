
#ifndef Slang_Core_Core_Script_h
#define Slang_Core_Core_Script_h


// Library includes

// Project includes
#include <Core/Common/Parameter.h>
#include <Core/Common/Types.h>

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Runtime {
	class Object;
}
class Symbol;
class VirtualMachine;

class Script
{
public:
	Script( VirtualMachine* vm );
	~Script() = default;

public:	//Helpers
	Symbol* resolve( const std::string& symbol );
	Symbol* resolveMethod( const std::string& method, const ParameterList& params );

public:	// Execution
	void execute( ThreadId threadId, const std::string& method, const ParameterList& params, Runtime::Object* result );

private:
	VirtualMachine* mVirtualMachine;
};


}


#endif
