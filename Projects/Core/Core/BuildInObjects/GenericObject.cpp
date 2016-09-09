
// Header
#include "GenericObject.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string GenericObject::DEFAULTVALUE = VALUE_NULL;
std::string GenericObject::TYPENAME = OBJECT;


GenericObject::GenericObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NULL)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	// this prevents the user to create an instance of 'Object'
	setImplementationType(ImplementationType::Abstract);
}

GenericObject::GenericObject(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value)
: Object(name, filename, type, value)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	// this prevents the user to create an instance of 'Object'
	setImplementationType(ImplementationType::Abstract);
}

GenericObject::GenericObject(const Object& object)
: Object(object.getName(), object.Filename(), object.Typename(), VALUE_NULL)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	// this prevents the user to create an instance of 'Object'
	setImplementationType(ImplementationType::Abstract);
}


}
}
