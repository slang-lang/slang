
#ifndef ObjectiveScript_Extensions_System_FromJson_h
#define ObjectiveScript_Extensions_System_FromJson_h


// Library includes
#include <Json/Parser.h>
#include <Json/Value.h>

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class FromJson : public ExtensionMethod
{
public:
	FromJson()
	: ExtensionMethod(0, "FromJsonString", Designtime::BoolObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("object", _any));
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			Runtime::Object *param_object = Controller::Instance().memory()->get((*it++).reference());
			if ( !param_object ) {
				throw Runtime::Exceptions::AccessViolation("invalid reference set for 'object'", token.position());
			}

			std::string param_value = (*it++).value().toStdString();

			bool success = param_object->FromJson(::Json::Parser::parse(param_value));

			*result = Runtime::BoolObject(success);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}

#endif
