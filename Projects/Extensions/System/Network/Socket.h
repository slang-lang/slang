
#ifndef Slang_Extensions_System_Network_Socket_h
#define Slang_Extensions_System_Network_Socket_h


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
	: ExtensionMethod(0, "socket", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("domain", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("type", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("protocol", Designtime::Int32Type::TYPENAME, 0, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_domain = (*it++).value().toInt();
		int param_type = (*it++).value().toInt();
		int param_protocol = (*it++).value().toInt();

		int handle = socket(param_domain, param_type, param_protocol);

		*result = Runtime::Int32Type(handle);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
