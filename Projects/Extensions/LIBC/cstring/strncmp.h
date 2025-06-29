
#ifndef Slang_Extensions_LIBC_cstring_strncmp_h
#define Slang_Extensions_LIBC_cstring_strncmp_h


// Library includes
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRNCMP : public ExtensionMethod
{
public:
	STRNCMP()
	: ExtensionMethod( 0, "strncmp", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str1", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "str2", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "num", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_str1 = (*it++).value().toStdString();
		auto param_str2 = (*it++).value().toStdString();
		auto param_num  = (*it++).value().toInt();

		*result = Runtime::Int32Type( strncmp( param_str1.c_str(), param_str2.c_str(), param_num ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
