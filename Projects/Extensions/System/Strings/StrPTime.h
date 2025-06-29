
#ifndef Slang_Extensions_System_StrPTime_h
#define Slang_Extensions_System_StrPTime_h


// Library includes
#include <ctime>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrPTime : public ExtensionMethod
{
public:
    StrPTime()
	: ExtensionMethod( 0, "strptime", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "format", Designtime::StringType::TYPENAME, 0 ) );
        params.push_back( Parameter::CreateDesigntime( "time", Designtime::StringType::TYPENAME, 0 ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		std::string param_format = (*it++).value().toStdString();
		std::string param_time = (*it++).value().toStdString();

		struct tm tm{};

		if ( strptime(param_time.c_str(), param_format.c_str(), &tm ) ) {
			auto time = mktime( &tm );

			*result = Runtime::Int32Type( time );
		}
		else {
			*result = Runtime::Int32Type( 0 );
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
