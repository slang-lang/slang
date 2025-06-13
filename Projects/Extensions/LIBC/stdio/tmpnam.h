
#ifndef Slang_Extensions_LIBC_stdio_tmpnam_h
#define Slang_Extensions_LIBC_stdio_tmpnam_h


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
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Runtime/Utils.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class TMPNAM : public ExtensionMethod
{
public:
	TMPNAM()
	: ExtensionMethod(0, "tmpnam", Designtime::StringType::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

#ifdef __APPLE__
		*result = Runtime::StringType( std::to_string( mkstemp( nullptr ) ) );  // tmpnam is deprecated
#else
		*result = Runtime::StringType( std::string( tmpnam( nullptr ) ) );
#endif

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
