
#ifndef ObjectiveScript_Common_TypeDeclaration_h
#define ObjectiveScript_Common_TypeDeclaration_h


// Library includes
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "PrototypeConstraint.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Common {


class TypeDeclaration
{
public:
	TypeDeclaration()
	: mMutability(Mutability::Modify)
	{ }
	TypeDeclaration(const std::string& type)
	: mCombinedName(type),
	  mMutability(Mutability::Modify),
	  mName(type)
	{ }
	TypeDeclaration(const TypeDeclaration& other)
	: mCombinedName(other.mCombinedName),
	  mConstraints(other.mConstraints),
	  mMutability(other.mMutability),
	  mName(other.mName)
	{ }
	TypeDeclaration(const std::string& type, const PrototypeConstraints& constraints, Mutability::E mutability = Mutability::Modify)
	: mCombinedName(type),
	  mConstraints(constraints),
	  mMutability(mutability),
	  mName(type)
	{ }

	bool operator==(const std::string& type) const {
		return mCombinedName.empty() ? (mName == type) : (mCombinedName == type);
	}

public:
	std::string mCombinedName;
	PrototypeConstraints mConstraints;
	Mutability::E mMutability;
	std::string mName;
};


}
}


#endif
