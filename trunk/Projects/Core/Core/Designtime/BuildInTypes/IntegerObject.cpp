
// Header
#include "IntegerObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


int IntegerObject::DEFAULTVALUE = 0;
std::string IntegerObject::TYPENAME = _int;


IntegerObject::IntegerObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& IntegerObject::getTypeName() const
{
	return TYPENAME;
}

void IntegerObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_int))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}
