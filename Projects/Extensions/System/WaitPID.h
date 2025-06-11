
#ifndef Slang_Extensions_System_WaitPID_h
#define Slang_Extensions_System_WaitPID_h


// Library includes
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class WaitPID : public ExtensionMethod
{
public:
	WaitPID()
	: ExtensionMethod( 0, "waitpid", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
        params.push_back( Parameter::CreateDesigntime( "pid", Designtime::Int32Type::TYPENAME ) );
        params.push_back( Parameter::CreateDesigntime( "options", Designtime::Int32Type::TYPENAME ) );

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
        ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		auto param_pid = (*it++).value().toInt();
		auto param_options = (*it++).value().toInt();

		int status;
		/*param_pid =*/ waitpid( param_pid, &status, param_options );

		*result = Runtime::Int32Type( status );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
