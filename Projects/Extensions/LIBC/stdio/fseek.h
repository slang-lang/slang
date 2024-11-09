
#ifndef Slang_Extensions_LIBC_stdio_fseek_h
#define Slang_Extensions_LIBC_stdio_fseek_h


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


class FSEEK : public ExtensionMethod
{
public:
	FSEEK()
	: ExtensionMethod( 0, "fseek", Designtime::Int32Type::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::Int32Type::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "offset", Designtime::Int32Type::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "origin", Designtime::Int32Type::TYPENAME, Runtime::AtomicValue( SEEK_SET ), true ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token )
	{
		ParameterList list = mergeParameters( params );

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();
			auto param_offset = (*it++).value().toInt();
			auto param_origin = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find( param_handle ) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
			}

			long size = fseek( stdio_t::FileHandles[param_handle], param_offset, param_origin );
			if ( size == -1 ) {
				throw Runtime::Exceptions::RuntimeException( "error while seeking file" );
			}

			*result = Runtime::Int32Type( static_cast<int32_t>( size ) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance( Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT );
			*data = Runtime::StringType( std::string( e.what() ) );

			Controller::Instance().thread( threadId )->exception() = Runtime::ExceptionData( data, token.position() );
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
