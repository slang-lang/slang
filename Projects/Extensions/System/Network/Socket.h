
#ifndef ObjectiveScript_Extensions_System_Network_Socket_h
#define ObjectiveScript_Extensions_System_Network_Socket_h


// Library includes
#include <sys/types.h>
#ifdef _MSC_VER
#	include <winsock.h>
#else
#	include <sys/socket.h>
#endif

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class Socket : public ExtensionMethod
{
public:
	Socket()
	: ExtensionMethod(0, "socket", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("domain", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("type", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("protocol", Designtime::IntegerObject::TYPENAME, 0, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_domain = (*it++).value().toInt();
			int param_type = (*it++).value().toInt();
			int param_protocol = (*it++).value().toInt();

			int handle = socket(param_domain, param_type, param_protocol);

			*result = Runtime::IntegerObject(handle);
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
