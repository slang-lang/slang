
#ifndef Slang_Extensions_System_Strings_StrFind_h
#define Slang_Extensions_System_Strings_StrFind_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrFind : public ExtensionMethod
{
public:
	StrFind()
	: ExtensionMethod(0, "strfind", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("source", Designtime::StringObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("target", Designtime::StringObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("position", Designtime::IntegerObject::TYPENAME, 0, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_source = (*it++).value().toStdString();
			std::string param_target = (*it++).value().toStdString();
			unsigned long param_position = (*it).value().toInt();

			int my_result = (int)param_source.find(param_target, param_position);

			*result = Runtime::IntegerObject(my_result);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
