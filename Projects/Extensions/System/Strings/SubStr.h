
#ifndef Slang_Extensions_System_Strings_SubStr_h
#define Slang_Extensions_System_Strings_SubStr_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class SubStr : public ExtensionMethod
{
public:
	SubStr()
	: ExtensionMethod(0, "substr", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("value", Designtime::StringType::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("start", Designtime::Int32Type::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("length", Designtime::Int32Type::TYPENAME, -1, true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_value = (*it++).value().toStdString();
			unsigned long param_start = (*it++).value().toInt();
			unsigned long param_end = std::string::npos;

			if ( params.size() >= 3 ) {
				param_end = (*it++).value().toInt();
			}

			std::string result_value = param_value.substr(param_start, param_end);

			*result = Runtime::StringType(result_value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

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
