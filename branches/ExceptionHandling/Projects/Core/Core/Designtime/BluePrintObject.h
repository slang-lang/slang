
#ifndef ObjectiveScript_Designtime_BluePrintObject_h
#define ObjectiveScript_Designtime_BluePrintObject_h


// Library includes
#include <string>

// Project includes
#include <Core/Runtime/AtomicValue.h>
#include <Core/Consts.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include "BluePrintGeneric.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class BluePrintObject : public BluePrintGeneric,
						public MethodScope
{
public:
	BluePrintObject();
	BluePrintObject(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintObject();

public:
	void setParent(IScope* parent);

	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);

	std::string ToString(unsigned int indent) const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

private:
	Runtime::AtomicValue mValue;
};


}
}


#endif
