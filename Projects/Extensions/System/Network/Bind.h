
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
	: ExtensionMethod(0, "bind", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("sockaddr", Common::TypeDeclaration("ISocketAddress")));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_sockfd = (*it++).value().toInt();
		Runtime::Object* param_addr = Controller::Instance().memory()->get((*it++).reference());

		int handle = evaluate(param_sockfd, param_addr);

		*result = Runtime::Int32Type(handle);

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

		sockaddr_in serv_addr;
		sa_family_t addr_family = static_cast<sa_family_t>( static_cast<Runtime::Int32Type*>( familySymbol )->getValue().toInt() );

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
		inet_pton(serv_addr.sin_family, static_cast<Runtime::StringType*>( addressSymbol )->getValue().toStdString().c_str(), &serv_addr.sin_addr);

		// set sa_port
		serv_addr.sin_port = static_cast<in_port_t>( static_cast<Runtime::Int32Type*>( portSymbol )->getValue().toInt() );
#endif

		return bind(param_sockfd, (sockaddr *) &serv_addr, sizeof(serv_addr));
	}
};


}
}
}
}


#endif
