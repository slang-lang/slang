
// Header
#include "BoolType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


bool BoolType::DEFAULTVALUE = false;
std::string BoolType::TYPENAME = _bool;


BoolType::BoolType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& BoolType::getTypeName() const
{
	return TYPENAME;
}

void BoolType::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_bool))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
