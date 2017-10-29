
#ifndef ObjectiveScript_Extensions_System_ToJson_h
#define ObjectiveScript_Extensions_System_ToJson_h


// Library includes
#include <Json/Value.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class ToJson : public ExtensionMethod
{
public:
	ToJson()
	: ExtensionMethod(0, "ToJsonString", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("source", VALUE_NONE));

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

			::Json::Value value = param_object->ToJson();

			*result = Runtime::StringObject(value.toString());
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
