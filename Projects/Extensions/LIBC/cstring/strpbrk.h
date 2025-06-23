
#ifndef Slang_Extensions_LIBC_cstring_strpbrk_h
#define Slang_Extensions_LIBC_cstring_strpbrk_h


// Library includes
#include <cassert>
#include <cstring>

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
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


class STRPBRK : public ExtensionMethod
{
public:
	STRPBRK()
	: ExtensionMethod( 0, "strpbrk", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "dest", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "breakset", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_dest     = (*it++).value().toStdString();
		auto param_breakset = (*it++).value().toStdString();

		*result = Runtime::StringType( std::string( strpbrk( param_dest.c_str(), param_breakset.c_str() ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
