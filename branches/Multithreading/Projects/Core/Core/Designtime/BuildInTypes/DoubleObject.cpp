
// Header
#include "DoubleObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


double DoubleObject::DEFAULTVALUE = 0.0;
std::string DoubleObject::TYPENAME = _double;


DoubleObject::DoubleObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& DoubleObject::getTypeName() const
{
	return TYPENAME;
}

void DoubleObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
            Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_double))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}
