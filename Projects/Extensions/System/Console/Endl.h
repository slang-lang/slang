
#ifndef Slang_Extensions_System_Console_Endl_h
#define Slang_Extensions_System_Console_Endl_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Console {


class Endl : public ExtensionMethod
{
public:
	Endl()
	: ExtensionMethod( 0, "endl", Designtime::StringType::TYPENAME )
	{
		ParameterList params;

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* /*result*/ )
	{
		if ( mOutMode == CERR ) {
			std::cerr << std::endl;
		}
		else if ( mOutMode == COUT ) {
			std::cout << std::endl;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
