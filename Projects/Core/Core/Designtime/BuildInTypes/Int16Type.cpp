
// Header
#include "Int16Type.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


int16_t Int16Type::DEFAULTVALUE = 0;
std::string Int16Type::TYPENAME = _int16;


Int16Type::Int16Type()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& Int16Type::getTypeName() const
{
	return TYPENAME;
}

void Int16Type::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.emplace_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_int16))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
