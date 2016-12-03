
#ifndef ObjectiveScript_Extensions_System_WriteLn_h
#define ObjectiveScript_Extensions_System_WriteLn_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class WriteLn : public ExtensionMethod
{
public:
	WriteLn()
	: ExtensionMethod(0, "writeln", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("text", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();

			std::cout << param_text << std::endl;
		}
		catch ( std::exception& e ) {
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
}


#endif
