
#ifndef Slang_Extensions_System_WaitPID_h
#define Slang_Extensions_System_WaitPID_h


// Library includes
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
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
	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token )
	{
        ParameterList list = mergeParameters( params );

        try {
            ParameterList::const_iterator it = list.begin();

            auto param_pid = (*it++).value().toInt();
            auto param_options = (*it++).value().toInt();

            int status;
            param_pid = waitpid( param_pid, &status, param_options );

            *result = Runtime::Int32Type( status );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance( Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT );
			*data = Runtime::StringObject( std::string( e.what() ) );

			Controller::Instance().thread( threadId )->exception() = Runtime::ExceptionData( data, token.position() );
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
