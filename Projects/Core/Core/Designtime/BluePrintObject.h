
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
						public MethodScope
{
public:
	BluePrintObject();
	BluePrintObject(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintObject();

public:
	void cleanup();

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

	bool isForwardDeclaration() const;
	void setForwardDeclaration(bool state);

	bool isInterface() const;
	void setInterface(bool state);

	void setParent(IScope* parent);

	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);

	virtual std::string ToString(unsigned int indent) const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

private:
	Ancestors mInheritance;
	bool mIsForwardDeclaration;
	bool mIsInterface;
	Runtime::AtomicValue mValue;
	Visibility::E mVisibility;
};


}
}


#endif
