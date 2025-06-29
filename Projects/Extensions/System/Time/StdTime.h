
#ifndef Slang_Extensions_System_Time_StdTime_h
#define Slang_Extensions_System_Time_StdTime_h


// Library includes
#include <ctime>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>

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
	: ExtensionMethod( nullptr, "time", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* result )
	{
		*result = Runtime::Int32Type( static_cast<int>( time( nullptr ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
