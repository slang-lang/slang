
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
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			Runtime::Object* param_object = Controller::Instance().memory()->get((*it++).reference());
			if ( !param_object ) {
				throw Runtime::Exceptions::AccessViolation("invalid reference set for 'object'", token.position());
			}

			::Json::Value param_value = ::Json::Parser::parse((*it++).value().toStdString());
			bool success = fromJson(param_value, param_object);

			*result = Runtime::BoolObject(success);
		}
		catch ( std::exception &e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	bool fromJson(const ::Json::Value& value, Runtime::Object* result) const {
		for ( ::Json::Value::Members::const_iterator it = value.members().begin(); it != value.members().end(); ++it ) {
			::Json::Value sub = (*it);

			Symbol *symbol = result->resolve(sub.key(), false, Visibility::Designtime);
			if ( !symbol ) {
				throw Common::Exceptions::Exception("FromJson: unknown member '" + sub.key() + "'!");
			}

			Runtime::Object *obj = dynamic_cast<Runtime::Object*>(symbol);
			if ( !obj ) {
				continue;
			}

			if ( obj->isAtomicType() ) {
				obj->setValue(sub.asString());
			}
			else {
				fromJson(sub, obj);
			}
		}

		return true;
	}
};


}
}

#endif
