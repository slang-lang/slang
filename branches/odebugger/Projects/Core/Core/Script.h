
#ifndef ObjectiveScript_Script_h
#define ObjectiveScript_Script_h


// Library includes

// Project includes
#include "Parameter.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
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

public:	//Helpers
	Symbol* resolve(const std::string &symbol);
	Symbol* resolveMethod(const std::string &method, const ParameterList &params);

public:	// Execution
	void execute(const std::string& method, const ParameterList& params, Runtime::Object* result);

protected:

private:
	Repository *mRepository;
};


}


#endif
