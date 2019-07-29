
// Header
#include "FloatObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


float FloatObject::DEFAULTVALUE = 0.f;
std::string FloatObject::TYPENAME = _float;


FloatObject::FloatObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& FloatObject::getTypeName() const
{
	return TYPENAME;
}

void FloatObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, _void);
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_float))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}
