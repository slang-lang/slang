
#ifndef Slang_Extensions_System_Console_Cerr_h
#define Slang_Extensions_System_Console_Cerr_h


// Library includes
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Console {


class Cerr : public ExtensionMethod
{
public:
	Cerr()
	: ExtensionMethod( 0, "cerr", Designtime::StringType::TYPENAME )
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

		std::cerr << (*it++).value().toStdString();

		mOutMode = CERR;

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
