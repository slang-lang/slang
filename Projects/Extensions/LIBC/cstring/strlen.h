
#ifndef Slang_Extensions_LIBC_cstring_strlen_h
#define Slang_Extensions_LIBC_cstring_strlen_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace cstring {


class STRLEN : public ExtensionMethod
{
public:
	STRLEN()
	: ExtensionMethod( 0, "strlen", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime( "value", Designtime::StringType::TYPENAME ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_value = (*it++).value().toStdString();

		*result = Runtime::Int32Type( static_cast<int32_t>( param_value.size() ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
