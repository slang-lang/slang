
// Header
#include "Strings.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Strings {


Object concat(Object& v1, Object& v2)
{
	return String(Tools::toString(v1.getValue() + v2.getValue()));
}

}
}
