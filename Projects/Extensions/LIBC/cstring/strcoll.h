
#ifndef Slang_Extensions_LIBC_cstring_strcoll_h
#define Slang_Extensions_LIBC_cstring_strcoll_h


// Library includes
#include <cassert>
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRCOLL : public ExtensionMethod
{
public:
	STRCOLL()
	: ExtensionMethod( 0, "strcoll", Designtime::Int32Type::TYPENAME )
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

		*result = Runtime::Int32Type( strcoll( param_str1.c_str(), param_str2.c_str() ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
