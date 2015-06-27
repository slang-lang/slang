
#ifndef ObjectiveScript_Interfaces_IExternalMethod_h
#define ObjectiveScript_Interfaces_IExternalMethod_h


// Library includes
#include <string>

// Project includes
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Object;

class IExternalMethod
{
public:
	virtual ~IExternalMethod() { }

	virtual Object* execute(const ParameterList& params) = 0;
};


}


#endif
