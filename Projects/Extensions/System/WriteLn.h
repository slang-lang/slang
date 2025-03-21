
#ifndef Slang_Extensions_System_WriteLn_h
#define Slang_Extensions_System_WriteLn_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class WriteLn : public ExtensionMethod
{
public:
	WriteLn()
	: ExtensionMethod(0, "writeln", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("text", Designtime::StringType::TYPENAME, Runtime::AtomicValue(std::string(VALUE_NONE)), true));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();

			std::cout << param_text << std::endl;
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


#endif
