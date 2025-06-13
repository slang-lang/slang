
#ifndef Slang_Extensions_LIBC_cstring_strncat_h
#define Slang_Extensions_LIBC_cstring_strncat_h


// Library includes
#include <cassert>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
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


class STRNCAT : public ExtensionMethod
{
public:
	STRNCAT()
	: ExtensionMethod( 0, "strncat", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "destination", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "source", Designtime::StringType::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "num", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_destination = (*it++).value().toStdString();
		auto param_source      = (*it++).value().toStdString();
		auto param_num         = (*it++).value().toInt();

		*result = Runtime::StringType( param_destination + param_source.substr( param_num ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
