
// Header
#include "DoubleType.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace Slang {
namespace Designtime {


double DoubleType::DEFAULTVALUE = 0.0;
std::string DoubleType::TYPENAME = _double;


DoubleType::DoubleType()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& DoubleType::getTypeName() const
{
	return TYPENAME;
}

void DoubleType::initialize()
{
	auto* constructor = new Common::Method(this, RESERVED_WORD_CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
            Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_double))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(RESERVED_WORD_CONSTRUCTOR, constructor);
}


}
}
