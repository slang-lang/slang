
#ifndef ObjectiveScript_Script_h
#define ObjectiveScript_Script_h


// Library includes

// Project includes
#include "Parameter.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
namespace Runtime {
	class Object;
}
class Repository;
class Symbol;

class Script
{
public:
	Script(Repository *repository);
	~Script();

public:	// Setup
	void assign(Runtime::Object *object);

public:	//Helpers
	Symbol* resolve(const std::string &symbol);
	Symbol* resolveMethod(const std::string &method, const ParameterList &params);

public:	// Execution
	Runtime::Object execute(const std::string& method, const ParameterList& params = ParameterList());

protected:

private:
	Runtime::Object *mObject;
	Repository *mRepository;
};


}


#endif
