
#ifndef Slang_Core_Designtime_BluePrintGeneric_h
#define Slang_Core_Designtime_BluePrintGeneric_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Common/PrototypeConstraint.h>
#include <Core/Common/Visibility.h>
#include <Core/Consts.h>
#include <Core/Designtime/Parser/Token.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include <Core/Types.h>
#include "Ancestor.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Designtime {


class BluePrintGeneric : public BlueprintSymbol
{
public:
	BluePrintGeneric();
	BluePrintGeneric(const std::string& unqualifiedTypename, const std::string& filename);
	virtual ~BluePrintGeneric();

public:
	const std::string& Filename() const;
	const std::string& QualifiedTypename() const;

	void setQualifiedTypename(const std::string& name);

public:
	// Inheritance
	// {
	Ancestors getAncestors() const;
	Ancestors getInheritance() const;
	Ancestors getImplementations() const;

	bool inheritsFrom(const std::string& type) const;

	void addInheritance(const Ancestor& inheritance);
	// }

	bool isAtomicType() const;
	bool isAbstract() const;
	bool isInterface() const;
	bool isPrototype() const;

	virtual bool isIterable() const = 0;

	const PrototypeConstraints& getPrototypeConstraints() const;
	void setPrototypeConstraints(const PrototypeConstraints& constraints);

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

protected:
	std::string mFilename;
	Ancestors mInheritance;
	bool mIsAtomicType;
	PrototypeConstraints mPrototypeConstraints;
	std::string mQualifiedTypename;
	TokenList mTokens;
	std::string mUnqualifiedTypename;
};


}
}


#endif
