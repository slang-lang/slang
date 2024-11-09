
// Header
#include "EnumerationType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace Slang {
namespace Designtime {


int32_t EnumerationType::DEFAULTVALUE = 0;
std::string EnumerationType::TYPENAME = _int32;


EnumerationType::EnumerationType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& EnumerationType::getTypeName() const
{
	return TYPENAME;
}

void EnumerationType::initialize()
{
	Common::Method* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
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
