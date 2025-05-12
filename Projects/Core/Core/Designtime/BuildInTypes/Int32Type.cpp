
// Header
#include "Int32Type.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


int32_t Int32Type::DEFAULTVALUE = 0;
std::string Int32Type::TYPENAME = _int32;


Int32Type::Int32Type()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& Int32Type::getTypeName() const
{
	return TYPENAME;
}

void Int32Type::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_int32))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
