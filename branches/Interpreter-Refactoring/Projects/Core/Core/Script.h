
#ifndef ObjectiveScript_Core_Script_h
#define ObjectiveScript_Core_Script_h


// Library includes

// Project includes
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class MethodScope;
namespace Runtime {
	class Object;
}
class Symbol;

class Script
{
public:
	Script(MethodScope* scope);
	~Script();

public:	//Helpers
	Symbol* resolve(const std::string &symbol);
	Symbol* resolveMethod(const std::string &method, const ParameterList &params);

public:	// Execution
	void execute(const std::string& method, const ParameterList& params, Runtime::Object* result);

protected:

private:
	MethodScope* mScope;
};


}


#endif
