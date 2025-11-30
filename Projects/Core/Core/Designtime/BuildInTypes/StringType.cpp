
// Header
#include "StringType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace Slang {
namespace Designtime {


std::string StringType::DEFAULTVALUE = "";
std::string StringType::TYPENAME = _string;


StringType::StringType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& StringType::getTypeName() const
{
	return TYPENAME;
}

void StringType::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.emplace_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_string))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
