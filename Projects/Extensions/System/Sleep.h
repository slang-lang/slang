
#ifndef Slang_Extensions_System_Sleep_h
#define Slang_Extensions_System_Sleep_h


// Library includes
#ifdef _WIN32
#	include <stdlib.h>
#else
	#include <chrono>
	#include <thread>
#endif

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class Sleep : public ExtensionMethod
{
public:
	Sleep()
	: ExtensionMethod(0, "sleep", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("millis", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			long param_millis = (*it++).value().toInt();

#ifdef _WIN32
			_sleep(param_millis);
#else
			std::this_thread::sleep_for(std::chrono::milliseconds(param_millis));
#endif
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


#endif
