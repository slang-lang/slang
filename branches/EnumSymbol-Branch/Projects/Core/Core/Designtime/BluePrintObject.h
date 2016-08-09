
#ifndef ObjectiveScript_Designtime_BluePrintObject_h
#define ObjectiveScript_Designtime_BluePrintObject_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Attributes/Visibility.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Consts.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include <Core/Types.h>
#include "Ancestor.h"
#include "BluePrintGeneric.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}

namespace Designtime {


class BluePrintObject : public BluePrintGeneric,
						public MethodScope,
						public BluePrintSymbol
{
public:
	BluePrintObject();
	BluePrintObject(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintObject();

public:
	virtual ISymbol::IType::E getSymbolType() const { return ISymbol::IType::BluePrintSymbol; }

public:
	void cleanup();

public:	// RTTI
	const std::string& Filename() const { return mFilename; }
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }
	const std::string& Typename() const { return mTypename; }

public:
	// Inheritance
	// {
	Designtime::Ancestors getAncestors() const;
	Designtime::Ancestors getInheritance() const;
	Designtime::Ancestors getImplementations() const;

	void addInheritance(const Designtime::Ancestor& inheritance);
	// }

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

	bool isAbstract() const;
	void setAbstract(bool state);

	bool isInterface() const;
	void setInterface(bool state);

	void setParent(IScope* parent);

	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);

	virtual std::string ToString() const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

private:
	Ancestors mInheritance;
	bool mIsInterface;
	Runtime::AtomicValue mValue;
	Visibility::E mVisibility;
};


}
}


#endif
