
#ifndef ObjectiveScript_Designtime_BluePrintEnum_h
#define ObjectiveScript_Designtime_BluePrintEnum_h


// Library includes
#include <list>
#include <map>
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


class BluePrintEnum : public BluePrintGeneric,
					  public MethodScope
{
public:
	BluePrintEnum();
	BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintEnum();

public:
	void setParent(IScope* parent);

	std::string ToString(unsigned int indent) const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

private:
};


}
}


#endif
