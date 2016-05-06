
// Header
#include "JsonExtension.h"

// Library includes

// Project includes
#include "FromJson.h"
#include "ToJson.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Json {


void JsonExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new FromJson());
	methods.push_back(new ToJson());
}


}
}
}