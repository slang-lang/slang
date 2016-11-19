
// Header
#include "ToJson.h"

// Library includes
#include <Json/Value.h>

// Project includes
#include <Core/BuildInObjects/GenericObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


ToJson::ToJson()
: ExtensionMethod(0, "ToJsonString", Designtime::StringObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("object", VALUE_NONE, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E ToJson::execute(const ParameterList &params, Runtime::Object *result, const Token &token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		Runtime::Object *param_object = (*it++).pointer();

		Json::Value value = param_object->ToJson();

		*result = Runtime::StringObject(value.toString());
	}
	catch (std::exception &e) {
		Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}
