
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
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace stdio {


class REWIND : public ExtensionMethod
{
public:
	REWIND()
	: ExtensionMethod( 0, "rewind", Designtime::VoidObject::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::IntegerObject::TYPENAME ) );

		setSignature( params );
	}

	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList &params, Runtime::Object */*result*/, const Token& token )
	{
		ParameterList list = mergeParameters( params );

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find( param_handle ) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
			}

			rewind( stdio_t::FileHandles[param_handle] );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance( Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT );
			*data = Runtime::StringObject( std::string( e.what() ) );

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