
#ifndef Slang_Extensions_LIBC_cstring_strcmp_h
#define Slang_Extensions_LIBC_cstring_strcmp_h


// Library includes
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRCMP : public ExtensionMethod
{
public:
	STRCMP()
	: ExtensionMethod( 0, "strcmp", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str1", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "str2", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_str1 = (*it++).value().toStdString();
		auto param_str2 = (*it++).value().toStdString();

		*result = Runtime::Int32Type( strcmp( param_str1.c_str(), param_str2.c_str() ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
