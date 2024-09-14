
// Header
#include "UserObject.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue UserObject::DEFAULTVALUE;
std::string UserObject::TYPENAME = _object;


UserObject::UserObject()
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	mIsAtomicType = false;
}

UserObject::UserObject( const std::string& name, const std::string& filename, const std::string& type, bool isReference )
: Object( name, filename, type, DEFAULTVALUE )
{
	mIsAtomicType = false;
	mIsReference = isReference;
}

UserObject::UserObject( const Object& object )
: Object( object.getName(), object.Filename(), object.QualifiedTypename(), object.getValue() )
{
	mIsAtomicType = false;
}


}
}
