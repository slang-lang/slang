
// Header
#include "VoidType.h"

// Library includes

// Project includes
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


std::string VoidType::TYPENAME = _void;


VoidType::VoidType()
: Object( ANONYMOUS_OBJECT, SYSTEM_LIBRARY, TYPENAME, AtomicValue() )
{
	mIsAtomicType = true;
}

VoidType::VoidType( const std::string& name )
: Object( name, SYSTEM_LIBRARY, TYPENAME, AtomicValue() )
{
	mIsAtomicType = true;
}

VoidType::VoidType( const Object& object )
: Object( object.getName(), SYSTEM_LIBRARY, TYPENAME, AtomicValue() )
{
	mIsAtomicType = true;
}

bool VoidType::isValid() const
{
	return false;
}

bool VoidType::operator_bool() const
{
	return false;
}


}
}
