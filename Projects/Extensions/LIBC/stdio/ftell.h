
#ifndef Slang_Extensions_LIBC_stdio_ftell_h
#define Slang_Extensions_LIBC_stdio_ftell_h


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
#include <Core/Runtime/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FTELL : public ExtensionMethod
{
public:
	FTELL()
	: ExtensionMethod(0, "ftell", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("stream", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_stream = (*it++).value().toInt();

		if ( stdio_t::FileHandles.find(param_stream) == stdio_t::FileHandles.end() ) {
			throw Runtime::Exceptions::RuntimeException("invalid file handle");
		}

		long size = ftell(stdio_t::FileHandles[param_stream]);
		if ( size == -1 ) {
			throw Runtime::Exceptions::RuntimeException("error while telling file");
		}

		*result = Runtime::Int32Type( static_cast<int32_t>( size ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
