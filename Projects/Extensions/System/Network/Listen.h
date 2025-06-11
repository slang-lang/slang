
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
	: ExtensionMethod(0, "listen", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("sockfd", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("backlog_queue_size", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_sockfd = (*it++).value().toInt();
		int param_backlog_queue_size = (*it++).value().toInt();

		int handle = listen(param_sockfd, param_backlog_queue_size);

		*result = Runtime::Int32Type(handle);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
