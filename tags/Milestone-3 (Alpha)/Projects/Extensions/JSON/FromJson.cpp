
// Header
#include "FromJson.h"


// Library includes
#include <Json/Parser.h>
#include <Json/Value.h>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/GenericObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/GenericObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


FromJson::FromJson()
: ExtensionMethod(0, "FromJsonString", Designtime::BoolObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("object", Designtime::GenericObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("value", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FromJson::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		Runtime::Object *param_object = (*it++).pointer();
		std::string param_value = (*it++).value().toStdString();

		bool success = param_object->FromJson(Json::Parser::parse(param_value));

		*result = Runtime::BoolObject(success);
	}
	catch ( std::exception &e ) {
		Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

}
}