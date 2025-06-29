
// Header
#include "Utils.h"

// Library includes

// Project includes
#include <Core/Object.h>

// Namespace declarations


namespace Slang {
namespace Runtime {


bool isTrue(const Runtime::Object& object)
{
	if ( object.isAtomicType() ) {
		return object.getValue().toBool();
	}

	return object.isValid();
}

bool isTrue(const Runtime::Object* object)
{
	if ( object->isAtomicType() ) {
		return object->getValue().toBool();
	}

	return object->isValid();
}


}
}
