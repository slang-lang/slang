
#ifndef Slang_Extensions_System_Network_Shutdown_h
#define Slang_Extensions_System_Network_Shutdown_h


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


class Shutdown : public ExtensionMethod
{
public:
	Shutdown()
	: ExtensionMethod(0, "shutdown", Designtime::Int32Type::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("param1", Designtime::Int32Type::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("param2", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		int param_1 = (*it++).value().toInt();
		int param_2 = (*it++).value().toInt();

		int handle = shutdown(param_1, param_2);

		*result = Runtime::Int32Type(handle);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
