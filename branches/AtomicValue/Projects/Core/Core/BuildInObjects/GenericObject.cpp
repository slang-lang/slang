
// Header
#include "GenericObject.h"

// Library includes

// Project includes
#include <Core/Utils/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


std::string GenericObject::DEFAULTVALUE = VALUE_NULL;
std::string GenericObject::TYPENAME = GENERIC_OBJECT;


GenericObject::GenericObject()
: Object(ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, VALUE_NULL)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	setAbstract(true);
	//setValue(VALUE_NULL);
}

GenericObject::GenericObject(const std::string& name, const std::string& filename, const std::string& type, const std::string& value)
: Object(name, filename, type, value)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	setAbstract(true);
	//setValue(value);
}

GenericObject::GenericObject(const Object& object)
: Object(object.getName(), object.Filename(), object.Typename(), VALUE_NULL)
{
	mIsAtomicType = false;
	mIsConstructed = false;

	setAbstract(true);
	setValue(object.getValue());
}

const std::string& GenericObject::getTypeName() const
{
	return TYPENAME;
}


}
}
