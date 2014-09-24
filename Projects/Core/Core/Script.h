
#ifndef ObjectiveScript_Script_h
#define ObjectiveScript_Script_h


// Library includes
#include <map>

// Project includes
#include "Object.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IPrinter;
//class Object;
class Repository;

class Script
{
public:
	Script(size_t id);
	~Script();

public:	// Setup
	void assign(Object *object);
	void init(Repository *r);

public:	// Constructor & Destructor
	void construct();
	void destruct();

public:	//Helpers
	//Variable& getMember(const std::string& m);		// throws UnknownIdentifer exxception
	Object& getMember(const std::string& m);		// throws UnknownIdentifer exxception
	bool hasMember(const std::string& m);
	bool hasMethod(const std::string& m);
	bool hasMethod(const std::string& m, const VariablesList& params);

public:	// Execution
	// {
	Object execute(const std::string& method, VariablesList params = VariablesList());
	// }

public:	// Debug only
	void connectPrinter(IPrinter *p);

protected:

private:
	size_t	mId;

	Object		*mObject;
	IPrinter	*mPrinter;
	Repository	*mRepository;
};


}


#endif
