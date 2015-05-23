
#ifndef ObjectiveScript_Script_h
#define ObjectiveScript_Script_h


// Library includes
#include <map>

// Project includes
#include "Parameter.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
class Memory;
class Object;
class Repository;

class Script
{
public:
	Script();
	~Script();

public:	// Setup
	void assign(Object *object);
	void connectMemory(Memory *m);
	void connectRepository(Repository *r);

public:	// Constructor & Destructor
	void construct(const ParameterList& params);
	void destruct();

public:	//Helpers
	Object* getMember(const std::string& m);
	bool hasMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const ParameterList& params);

public:	// Execution
	// {
	Object execute(const std::string& method, ParameterList params = ParameterList());
	// }

public:	// Debug only
	void connectPrinter(IPrinter *p);

protected:

private:
	Memory		*mMemory;
	Object		*mObject;
	IPrinter	*mPrinter;
	Repository	*mRepository;
};


}


#endif
