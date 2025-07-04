
#ifndef Slang_Extensions_System_Network_Close_h
#define Slang_Extensions_System_Network_Close_h


// Library includes
#include <sys/types.h>
#ifdef _MSC_VER
#	include <io.h>
#	include <winsock.h>
#else
#	include <sys/socket.h>
#	include <arpa/inet.h>
#	include <unistd.h>
#endif

// Project includes
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


class Close : public ExtensionMethod
{
public:
	Close()
	: ExtensionMethod(0, "close", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_sockfd = (*it++).value().toInt();

		int handle = close(param_sockfd);

		*result = Runtime::Int32Type(handle);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
