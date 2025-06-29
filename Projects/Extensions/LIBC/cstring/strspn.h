
#ifndef Slang_Extensions_LIBC_cstring_strspn_h
#define Slang_Extensions_LIBC_cstring_strspn_h


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


class STRSPN : public ExtensionMethod
{
public:
	STRSPN()
	: ExtensionMethod( 0, "strspn", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "dest", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "src", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_dest = (*it++).value().toStdString();
		auto param_src  = (*it++).value().toStdString();

		*result = Runtime::Int32Type( strspn( param_dest.c_str(), param_src.c_str() ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
