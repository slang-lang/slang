
#ifndef ObjectiveScript_Extensions_System_Network_Send_h
#define ObjectiveScript_Extensions_System_Network_Send_h


// Library includes
#include <sys/types.h>
#include <sys/socket.h>

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Network {


class Send : public ExtensionMethod
{
public:
	Send()
	: ExtensionMethod(0, "send", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		//params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::IntegerObject::TYPENAME));
		//params.push_back(Parameter::CreateDesigntime("addr", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

/*
			int param_sockfd = (*it++).value().toInt();
			std::string param_addr = (*it++).value().toStdString();

			auto addr = new sockaddr();
			sprintf(addr->sa_data, "%s", param_addr.c_str());

			int handle = bind(param_sockfd, addr, param_addr.length());

			*result = Runtime::IntegerObject(handle);
*/
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
}


#endif