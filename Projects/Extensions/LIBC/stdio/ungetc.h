
#ifndef Slang_Extensions_LIBC_stdio_ungetc_h
#define Slang_Extensions_LIBC_stdio_ungetc_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/Int32Type.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class UNGETC : public ExtensionMethod
{
	static const int32_t READ_SIZE = 1024;

public:
	UNGETC()
	: ExtensionMethod( 0, "ungetc", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "ch", Designtime::Int32Type::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		auto param_ch     = (*it++).value().toInt();
		auto param_stream = (*it++).value().toInt();

		if ( stdio_t::FileHandles.find( param_stream ) == stdio_t::FileHandles.end() ) {
			throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
		}

		*result = Runtime::Int32Type( ungetc( param_ch, stdio_t::FileHandles[ param_stream ] ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
