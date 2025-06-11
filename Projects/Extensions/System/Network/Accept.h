
#ifndef Slang_Extensions_System_Network_Accept_h
#define Slang_Extensions_System_Network_Accept_h


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


class Accept : public ExtensionMethod
{
public:
	Accept()
	: ExtensionMethod(0, "accept", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		auto list = mergeParameters(params);

		auto it = list.begin();

		auto param_sockfd = (*it++).value().toInt();

		auto return_handle = accept(param_sockfd, nullptr, nullptr);

		*result = Runtime::Int32Type(return_handle);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
