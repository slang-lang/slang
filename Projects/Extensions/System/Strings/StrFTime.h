
#ifndef Slang_Extensions_System_StrFTime_h
#define Slang_Extensions_System_StrFTime_h


// Library includes
#include <ctime>
#include <iomanip>
#include <iostream>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Strings {


class StrFTime : public ExtensionMethod
{
public:
	StrFTime()
	: ExtensionMethod( 0, "strftime", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "format", Designtime::StringType::TYPENAME, 0 ) );
        params.push_back( Parameter::CreateDesigntime( "time", Designtime::Int32Type::TYPENAME, 0, true ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		std::string param_format = (*it++).value().toStdString();
		int32_t param_time = (*it++).value().toInt();

		std::time_t time;
		if ( param_time ) {
			time = param_time;
		}
		else {
			time = std::time( nullptr );
		}

		std::tm tm = *std::localtime( &time );

		std::stringstream ssr;
		ssr << std::put_time( &tm, param_format.c_str() );

		*result = Runtime::StringType( ssr.str() );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
