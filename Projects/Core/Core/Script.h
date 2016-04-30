
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
	Script();
	~Script();

public:	// Setup
	void assign(Runtime::Object *object);
	void connectRepository(Repository *r);

public:	// Constructor & Destructor
	void construct(const ParameterList& params);
	void destruct();

public:	//Helpers
	bool hasBeenConstructed() const;
	Symbol* resolve(const std::string &symbol);
	Symbol* resolveMethod(const std::string &method, const ParameterList &params);

public:	// Execution
	Runtime::Object execute(const std::string& method, const ParameterList& params = ParameterList());

protected:

private:
	bool mHasBeenConstructed;
	Runtime::Object *mObject;
	Repository *mRepository;
};


}


#endif
