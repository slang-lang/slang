
// Header
#include "UserType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace Slang {
namespace Designtime {


std::string UserType::DEFAULTVALUE = VALUE_NONE;
std::string UserType::TYPENAME = _object;


UserType::UserType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	initialize();
}

const std::string& UserType::getTypeName() const
{
	return TYPENAME;
}

void UserType::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
