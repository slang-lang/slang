
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
: MethodScope(ANONYMOUS_OBJECT, 0)
{
	mName = ANONYMOUS_OBJECT;
	mType = Symbol::IType::BluePrintObjectSymbol;
}

BluePrintObject::BluePrintObject(const std::string& type, const std::string& filename, const std::string& name)
: BluePrintGeneric(type, filename),
  MethodScope(type, 0)
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

bool BluePrintObject::hasDefaultConstructor() const
{
	for ( MethodCollection::const_iterator it = mMethods.begin(); it != mMethods.end(); ++it ) {
		if ( (*it)->getMethodType() == MethodAttributes::MethodType::Constructor &&
			(*it)->getName() == CONSTRUCTOR &&
			(*it)->provideSignature().empty() ) {
			// method has to be of type constructor without any parameters
			return true;
		}
	}

	return false;
}

MethodScope::MethodCollection BluePrintObject::provideMethods() const
{
	return mMethods;
}

Symbols BluePrintObject::provideSymbols() const
{
	return mSymbols;
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
