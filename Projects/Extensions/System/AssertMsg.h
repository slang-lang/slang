
#ifndef ObjectiveScript_Extensions_System_Assert_h
#define ObjectiveScript_Extensions_System_Assert_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class Assert : public ExtensionMethod
{
public:
	Assert()
	: ExtensionMethod(0, "assert", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("condition", _any));
		params.push_back(Parameter::CreateDesigntime("message", Designtime::StringObject::TYPENAME, Runtime::AtomicValue(VALUE_NONE), true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		Runtime::Reference param_reference = (*it).reference();
		Runtime::AtomicValue param_value = (*it++).value();
		std::string param_text = (*it++).value().toStdString();

		bool success = false;

		if ( param_reference.isValid() ) {
			Runtime::Object* condition = Controller::Instance().memory()->get(param_reference);

			success = isTrue(condition);
		}
		else {
			Runtime::Object tmp;
			tmp.setValue(param_value);

			success = isTrue(tmp);
		}

		if ( !success ) {
			throw Runtime::Exceptions::AssertionFailed(param_text, token.position());
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
