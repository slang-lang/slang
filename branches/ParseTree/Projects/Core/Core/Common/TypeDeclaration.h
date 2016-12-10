
#ifndef ObjectiveScript_Common_TypeDeclaration_h
#define ObjectiveScript_Common_TypeDeclaration_h


// Library includes
#include <string>

// Project includes
#include "PrototypeConstraint.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class TypeDeclaration
{
public:
	PrototypeConstraints mConstraints;
	std::string mTypename;
};


}


#endif
