
#ifndef Slang_Extensions_System_Strings_StrRPad_h
#define Slang_Extensions_System_Strings_StrRPad_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrRPad : public ExtensionMethod
{
public:
	StrRPad()
	: ExtensionMethod(0, "strrpad", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("length", Designtime::IntegerObject::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("pattern", Designtime::StringObject::TYPENAME, 0));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_value = (*it++).value().toStdString();
			int param_length = (*it++).value().toInt();
			std::string param_pattern = (*it++).value().toStdString();

			if ( param_length < 0 ) {
				throw Runtime::Exceptions::SizeException("invalid length");
			}
			if ( param_pattern.size() != 1 ) {
				throw Runtime::Exceptions::SizeException("invalid pattern size");
			}

			if ( (size_t)param_length > param_value.size() ) {
			    param_value.append(param_length - param_value.size(), param_pattern[0]);
            }

			*result = Runtime::StringObject(param_value);
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
