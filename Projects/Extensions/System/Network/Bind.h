
#ifndef Slang_Extensions_System_Network_Bind_h
#define Slang_Extensions_System_Network_Bind_h


// Library includes
#include <sys/types.h>
#ifdef _MSC_VER
#	include <winsock.h>
#	define sa_family_t u_short
#else
#	include <arpa/inet.h>
#	include <netinet/in.h>
#	include <sys/socket.h>
#	include <sys/un.h>
#endif

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class Bind : public ExtensionMethod
{
public:
	Bind()
	: ExtensionMethod(0, "bind", Designtime::IntegerObject::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("sockaddr", Common::TypeDeclaration("ISocketAddress")));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
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

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	int evaluate(int param_sockfd, Runtime::Object* param_addr) const {
		Symbol* addressSymbol = param_addr->resolve("_sa_address", true, Visibility::Public);
		if ( !addressSymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_address symbol not found");
		}

		Symbol* familySymbol = param_addr->resolve("_sa_family", true, Visibility::Public);
		if ( !familySymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_family symbol not found");
		}

		Symbol* portSymbol = param_addr->resolve("_sa_port", true, Visibility::Public);
		if ( !portSymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_port symbol not found");
		}

		struct sockaddr_in serv_addr;
		sa_family_t addr_family = (sa_family_t)static_cast<Runtime::IntegerObject*>(familySymbol)->getValue().toInt();

		// set sa_family
		switch ( addr_family ) {
			case AF_INET: {
				serv_addr.sin_family = AF_INET;
			} break;
#ifdef _MSC_VER
#else
			case AF_INET6: {
				serv_addr.sin_family = AF_INET6;
			} break;
#endif
			default:
				throw Common::Exceptions::Exception("unsupported socket address type provided!");
		}

#ifdef _MSC_VER
#else
		// set sa_address
		inet_pton(serv_addr.sin_family, static_cast<Runtime::StringObject*>(addressSymbol)->getValue().toStdString().c_str(), &serv_addr.sin_addr);

		// set sa_port
		serv_addr.sin_port = (in_port_t)static_cast<Runtime::IntegerObject*>(portSymbol)->getValue().toInt();
#endif

		return bind(param_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	}
};


}
}
}
}


#endif
