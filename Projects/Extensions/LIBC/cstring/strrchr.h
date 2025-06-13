
#ifndef Slang_Extensions_LIBC_cstring_strrchr_h
#define Slang_Extensions_LIBC_cstring_strrchr_h


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
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRRCHR : public ExtensionMethod
{
public:
	STRRCHR()
	: ExtensionMethod( 0, "strrchr", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "str", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "ch", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_str = (*it++).value().toStdString();
		auto param_ch  = (*it++).value().toInt();

		*result = Runtime::StringType( std::string( strrchr( param_str.c_str(), param_ch ) ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
