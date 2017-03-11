
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string UserObject::DEFAULTVALUE = VALUE_NONE;
std::string UserObject::TYPENAME = _object;


UserObject::UserObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	initialize();
}

const std::string& UserObject::getTypeName() const
{
	return TYPENAME;
}

void UserObject::initialize()
{
	// nothing to do here atm
}


}
}
