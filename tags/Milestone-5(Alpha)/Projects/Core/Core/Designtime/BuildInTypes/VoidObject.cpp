
// Header
#include "VoidObject.h"

// Library includes

// Project includes
#include <Core/Common/Method.h>
#include <Core/Consts.h>


// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


std::string VoidObject::TYPENAME = _void;


VoidObject::VoidObject()
: BluePrintObject(TYPENAME, SYSTEM_LIBRARY)
{
	mIsAtomicType = true;

	initialize();
}

const std::string& VoidObject::getTypeName() const
{
	return TYPENAME;
}

void VoidObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, Common::TypeDeclaration(_void));
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, Common::TypeDeclaration(_void))
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}