
// Header
#include "Strings.h"

// Library includes

// Project includes
#include <Core/BuildInObjects/String.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Strings {


Variable concat(const Variable& v1, const Variable& v2)
{
	return String(Tools::toString(v1.value() + v2.value()));
}

}
}
