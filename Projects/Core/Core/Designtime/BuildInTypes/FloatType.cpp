
// Header
#include "FloatType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace Slang {
namespace Designtime {


float FloatType::DEFAULTVALUE = 0.f;
std::string FloatType::TYPENAME = _float;


FloatType::FloatType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& FloatType::getTypeName() const
{
	return TYPENAME;
}

void FloatType::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_float))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
