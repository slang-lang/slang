
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

	//addInheritance(Ancestor(_object, Ancestor::Type::Extends, Visibility::Public));

	initialize();
}

const std::string& VoidObject::getTypeName() const
{
	return TYPENAME;
}

void VoidObject::initialize()
{
	Common::Method* constructor = new Common::Method(this, CONSTRUCTOR, _void);
	{
		ParameterList params;
		params.push_back(
			Parameter::CreateDesigntime(ANONYMOUS_OBJECT, _void)
		);
		constructor->setSignature(params);
		constructor->setVisibility(Visibility::Public);
	}

	defineMethod(CONSTRUCTOR, constructor);
}


}
}
