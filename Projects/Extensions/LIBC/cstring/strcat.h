
#ifndef Slang_Extensions_LIBC_cstring_strcat_h
#define Slang_Extensions_LIBC_cstring_strcat_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRCAT : public ExtensionMethod
{
public:
	STRCAT()
	: ExtensionMethod( 0, "strcat", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "destination", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "source", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_destination = (*it++).value().toStdString();
		auto param_source      = (*it++).value().toStdString();

		*result = Runtime::StringType( param_destination + param_source );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
