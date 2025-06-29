
#ifndef Slang_Extensions_System_Console_Cout_h
#define Slang_Extensions_System_Console_Cout_h


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


class Cout : public ExtensionMethod
{
public:
	Cout()
	: ExtensionMethod( 0, "cout", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "text", Common::TypeDeclaration( Designtime::StringType::TYPENAME ), VALUE_NONE, true ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* /*result*/ )
	{
		auto list = mergeParameters( params );

		auto it = list.begin();

		std::cout << (*it++).value().toStdString();

		mOutMode = COUT;

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
