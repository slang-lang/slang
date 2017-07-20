
#ifndef ObjectiveScript_Extensions_System_Network_Bind_h
#define ObjectiveScript_Extensions_System_Network_Bind_h


// Library includes
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Network {


class Bind : public ExtensionMethod
{
public:
	Bind()
	: ExtensionMethod(0, "bind", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("sockaddr", "ISocketAddress"));
		//params.push_back(Parameter::CreateDesigntime("sockaddr", "IPAddress"));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_sockfd = (*it++).value().toInt();
			Runtime::Object* param_addr = Controller::Instance().memory()->get((*it++).reference());

			int handle = evaluate(param_sockfd, param_addr);

			*result = Runtime::IntegerObject(handle);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	int evaluate(int param_sockfd, Runtime::Object *param_addr) const {
		// sa_family
		Symbol* sa_family = param_addr->resolve("_sa_family", true, Visibility::Public);
		sa_family_t addr_family = static_cast<Runtime::IntegerObject*>(sa_family)->getValue().toInt();

		switch ( addr_family ) {
			case AF_INET: {
				struct sockaddr_in serv_addr;
				serv_addr.sin_family = AF_INET;
				serv_addr.sin_addr.s_addr = INADDR_ANY;
				serv_addr.sin_port = param_addr->getValue().toInt();

				return bind(param_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
			} break;
			case AF_INET6: {
				struct sockaddr_in serv_addr;
				serv_addr.sin_family = AF_INET6;
				serv_addr.sin_addr.s_addr = INADDR_ANY;
				serv_addr.sin_port = param_addr->getValue().toInt();

				return bind(param_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
			} break;
			default: {
				throw Common::Exceptions::Exception("unsupported socket address type provided!");
			} break;
		}

		return -1;
	}
};


}
}
}
}


#endif
