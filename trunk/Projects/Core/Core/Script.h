
#ifndef ObjectiveScript_Script_h
#define ObjectiveScript_Script_h


// Library includes

// Project includes
#include "Parameter.h"
#include "Stack.h"
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

	void connectPrinter(IPrinter *p);
	void connectRepository(Repository *r);

public:	// Constructor & Destructor
	void construct(const ParameterList& params);
	void destruct();

public:	//Helpers
	Object* getMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const ParameterList& params);

public:	// Execution
	Object execute(const std::string& method, const ParameterList& params = ParameterList());

protected:

private:
	Object *mObject;
	IPrinter *mPrinter;
	Repository *mRepository;
	StackTrace mStackTrace;
};


}


#endif
