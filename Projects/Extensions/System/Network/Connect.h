
#ifndef Slang_Extensions_System_Network_Connect_h
#define Slang_Extensions_System_Network_Connect_h


// Library includes
#include <sys/types.h>
#ifdef _MSC_VER
#	include <winsock.h>
#else
#	include <sys/socket.h>
#	include <arpa/inet.h>
#endif

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class Connect : public ExtensionMethod
{
public:
	Connect()
	: ExtensionMethod(0, "connect", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::Int32Type::TYPENAME));
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

			*result = Runtime::Int32Type(handle);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	int evaluate(int param_sockfd, Runtime::Object* param_addr) const {
		auto* addressSymbol = param_addr->resolve("_sa_address", true, Visibility::Public);
		if ( !addressSymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_address symbol not found");
		}

		auto* familySymbol = param_addr->resolve("_sa_family", true, Visibility::Public);
		if ( !familySymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_family symbol not found");
		}

		auto* portSymbol = param_addr->resolve("_sa_port", true, Visibility::Public);
		if ( !portSymbol ) {
			throw Runtime::Exceptions::RuntimeException("_sa_port symbol not found");
		}

		struct sockaddr_in serv_addr;
		sa_family_t addr_family = static_cast<sa_family_t>( static_cast<Runtime::Int32Type*>(familySymbol)->getValue().toInt() );

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
		inet_pton(serv_addr.sin_family, static_cast<Runtime::StringType*>(addressSymbol)->getValue().toStdString().c_str(), &serv_addr.sin_addr);

		// set sa_port
		serv_addr.sin_port = (in_port_t)static_cast<Runtime::Int32Type*>(portSymbol)->getValue().toInt();
#endif

		return connect(param_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	}
};


}
}
}
}


#endif
