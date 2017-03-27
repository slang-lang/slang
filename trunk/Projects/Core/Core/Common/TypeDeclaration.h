
#ifndef ObjectiveScript_Common_TypeDeclaration_h
#define ObjectiveScript_Common_TypeDeclaration_h


// Library includes
#include <string>

// Project includes
#include "PrototypeConstraint.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


class TypeDeclaration
{
public:
	TypeDeclaration()
	{ }
	TypeDeclaration(const char* type)
	: mName(type)
	{ }
	TypeDeclaration(const std::string& type)
	: mName(type)
	{ }
	TypeDeclaration(const std::string& type, const PrototypeConstraints& constraints)
	: mConstraints(constraints),
	  mName(type)
	{ }

public:
	PrototypeConstraints mConstraints;
	std::string mName;
};


}
}


#endif
