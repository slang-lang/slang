
#ifndef ObjectiveScript_Common_TypeDeclaration_h
#define ObjectiveScript_Common_TypeDeclaration_h


// Library includes
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "PrototypeConstraint.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Common {


class TypeDeclaration
{
public:
	TypeDeclaration()
	: mMutability(Mutability::Modify)
	{ }
	TypeDeclaration(const char* type)
	: mMutability(Mutability::Modify),
	  mName(type)
	{ }
	TypeDeclaration(const std::string& type)
	: mCombinedName(type),
	  mMutability(Mutability::Modify),
	  mName(type)
	{ }
	TypeDeclaration(const std::string& type, const PrototypeConstraints& constraints, Mutability::E mutability = Mutability::Modify)
	: mCombinedName(type),
	  mConstraints(constraints),
	  mMutability(mutability),
	  mName(type)
	{ }

public:
	std::string mCombinedName;
	PrototypeConstraints mConstraints;
	Mutability::E mMutability;
	std::string mName;
};


}
}


#endif
