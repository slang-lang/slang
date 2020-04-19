
#ifndef Slang_Extensions_System_Network_Listen_h
#define Slang_Extensions_System_Network_Listen_h


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


class Listen : public ExtensionMethod
{
public:
	Listen()
	: ExtensionMethod(0, "listen", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("backlog_queue_size", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_sockfd = (*it++).value().toInt();
			int param_backlog_queue_size = (*it++).value().toInt();

			int handle = listen(param_sockfd, param_backlog_queue_size);

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
