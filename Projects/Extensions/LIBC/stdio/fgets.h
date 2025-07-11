
#ifndef Slang_Extensions_LIBC_stdio_fgets_h
#define Slang_Extensions_LIBC_stdio_fgets_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FGETS : public ExtensionMethod
{
	static constexpr int32_t READ_SIZE = 1024;

public:
	FGETS()
	: ExtensionMethod( 0, "fgets", Designtime::StringType::TYPENAME )
	{
		ParameterList params;
		params.push_back( Parameter::CreateDesigntime( "stream", Designtime::Int32Type::TYPENAME ) );
		params.push_back( Parameter::CreateDesigntime( "size", Designtime::Int32Type::TYPENAME ) );

		setSignature( params );
	}

public:
	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters( params );

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();
		auto param_size   = (*it++).value().toInt();

		if ( stdio_t::FileHandles.find( param_handle ) == stdio_t::FileHandles.end() ) {
			throw Runtime::Exceptions::RuntimeException( "invalid file handle" );
		}

		int32_t remainingSize{0};
		while ( remainingSize < param_size ) {
			auto readSize = param_size - remainingSize;
			if ( readSize > READ_SIZE ) {
				readSize = READ_SIZE;
			}

			char stream[READ_SIZE];
			if ( fgets( stream, readSize, stdio_t::FileHandles[ param_handle ] ) != nullptr ) {
				*result = Runtime::StringType( std::string( stream ) );
			}

			remainingSize += readSize;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
