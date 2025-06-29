
#ifndef Slang_Extensions_System_Fork_h
#define Slang_Extensions_System_Fork_h


// Library includes
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


class Fork : public ExtensionMethod
{
public:
	Fork()
	: ExtensionMethod(0, "fork", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* result )
	{
		*result = Runtime::Int32Type(fork());

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
