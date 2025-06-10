
// Header
#include "UserType.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue UserType::DEFAULTVALUE;
std::string UserType::TYPENAME = _object;


UserType::UserType()
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, DEFAULTVALUE )
{
	mIsAtomicType = false;
}

UserType::UserType( const std::string& name, const std::string& filename, const std::string& type, bool isReference )
: Object( name, filename, type, DEFAULTVALUE )
{
	mIsAtomicType = false;
	mIsReference = isReference;
}

UserType::UserType( const Object& object )
: Object( object.getName(), object.Filename(), object.QualifiedTypename(), object.getValue() )
{
	mIsAtomicType = false;
}


}
}
