
#ifndef Slang_Extensions_LIBC_stdio_rewind_h
#define Slang_Extensions_LIBC_stdio_rewind_h


// Library includes
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <unistd.h>
#endif

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class REWIND : public ExtensionMethod
{
public:
	REWIND()
	: ExtensionMethod( 0, "rewind", Designtime::VoidType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object */*result*/ )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();

		if ( stdio_t::FileHandles.find( param_handle ) == stdio_t::FileHandles.end() ) {
			throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
		}

		rewind( stdio_t::FileHandles[param_handle] );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
