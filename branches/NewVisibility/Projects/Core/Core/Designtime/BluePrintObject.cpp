
// Header
#include "BluePrintObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


BluePrintObject::BluePrintObject()
: MethodScope(ANONYMOUS_OBJECT, 0),
  mIsReference(false)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0),
  mIsReference(false)
{
	mName = name;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::~BluePrintObject()
{
}

Runtime::AtomicValue BluePrintObject::getValue() const
{
	return mValue;
}

bool BluePrintObject::hasConstructor() const
{
	// return any (private, protected, public) constructor that has or has no parameters or only default parameters
	Symbol* constructor = resolve(CONSTRUCTOR, true, Visibility::Public);
	if ( constructor && dynamic_cast<class MethodSymbol*>(constructor) ) {
		return true;
	}

	return false;
}

bool BluePrintObject::hasDefaultConstructor() const
{
	// return any (private, protected, public) constructor that has no parameters or only default parameters
	return resolveMethod(CONSTRUCTOR, ParameterList(), true, Visibility::Public) != NULL;
}

bool BluePrintObject::isReference() const
{
	return mIsReference;
}

MethodScope::MethodCollection BluePrintObject::provideMethods() const
{
	return mMethods;
}

Symbols BluePrintObject::provideSymbols() const
{
	return mSymbols;
}

void BluePrintObject::setIsReference(bool state)
{
	mIsReference = state;
}

void BluePrintObject::setParent(IScope* parent)
{
	mParent = parent;
}

void BluePrintObject::setValue(Runtime::AtomicValue value)
{
	mValue = value;
}

std::string BluePrintObject::ToString(unsigned int indent) const
{
	return ::Utils::Tools::indent(indent) + QualifiedTypename() + " " + getName();
}


}
}
