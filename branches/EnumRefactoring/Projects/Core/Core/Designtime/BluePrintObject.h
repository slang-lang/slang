
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

// Forward declarations
class Repository;

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

	bool hasConstructor() const;
	bool hasDefaultConstructor() const;

	bool isIterable() const;

	bool isPrepared() const;
	void prepareParents(Repository* repository);

	bool isReference() const;
	void setIsReference(bool state);

	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);

	std::string ToString(unsigned int indent) const;

public:
	BluePrintObject* fromPrototype(const PrototypeConstraints& constraints) const;
	BluePrintObject* replicate(const std::string& newType, const std::string& filename) const;

public:
	MethodCollection provideMethods() const;
	Symbols provideSymbols() const;

private:
	bool mIsPrepared;
	bool mIsReference;
	Runtime::AtomicValue mValue;
};


}
}


#endif
