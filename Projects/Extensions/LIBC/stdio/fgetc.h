
#ifndef Slang_Extensions_LIBC_stdio_fgetc_h
#define Slang_Extensions_LIBC_stdio_fgetc_h


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


class FGETC : public ExtensionMethod
{
	static const int32_t READ_SIZE = 1024;

public:
	FGETC()
	: ExtensionMethod( 0, "fgetc", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token )
	{
		ParameterList list = mergeParameters( params );

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_stream = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find( param_stream ) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
			}

			*result = Runtime::StringType( std::to_string( fgetc( stdio_t::FileHandles[ param_stream ] ) ) );
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
