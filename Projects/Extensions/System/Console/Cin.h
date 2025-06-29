
#ifndef Slang_Extensions_System_Console_Cin_h
#define Slang_Extensions_System_Console_Cin_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Console {


class Cin : public ExtensionMethod
{
public:
	Cin()
	: ExtensionMethod( 0, "cin", Designtime::StringType::TYPENAME )
	{
		ParameterList params;

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& /*params*/, Runtime::Object* result )
	{
		std::string text;

		getline( std::cin >> std::ws, text );
		std::cin.clear();

		*result = Runtime::StringType( text );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
