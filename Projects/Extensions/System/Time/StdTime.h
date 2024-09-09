
#ifndef Slang_Extensions_System_Time_StdTime_h
#define Slang_Extensions_System_Time_StdTime_h


// Library includes
#include <ctime>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Time {


class StdTime : public ExtensionMethod
{
public:
	StdTime()
	: ExtensionMethod( nullptr, "time", Designtime::IntegerObject::TYPENAME )
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList& /*params*/, Runtime::Object* result, const Token& token )
	{
		try {
			*result = Runtime::IntegerObject( static_cast<int>( time( nullptr ) ) );
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
}


#endif
