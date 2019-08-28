
// Header
#include "BoolObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


bool BoolObject::DEFAULTVALUE = false;
std::string BoolObject::TYPENAME = _bool;


BoolObject::BoolObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& BoolObject::getTypeName() const
{
	return TYPENAME;
}

void BoolObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_bool))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}
