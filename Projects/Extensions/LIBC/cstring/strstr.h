
#ifndef Slang_Extensions_LIBC_cstring_strstr_h
#define Slang_Extensions_LIBC_cstring_strstr_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRSTR : public ExtensionMethod
{
public:
	STRSTR()
	: ExtensionMethod( 0, "strstr", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str", Designtime::StringType::TYPENAME, 0 ) );
		params.push_back( Parameter::CreateDesigntime( "substr", Designtime::Int32Type::TYPENAME, 0 ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		auto param_str    = (*it++).value().toStdString();
		auto param_substr = (*it++).value().toStdString();

		*result = Runtime::StringType( std::string( strstr( param_str.c_str(), param_substr.c_str() ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
