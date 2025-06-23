
#ifndef Slang_Extensions_LIBC_stdio_getchar_h
#define Slang_Extensions_LIBC_stdio_getchar_h


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
#include <Core/Runtime/Utils.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class GETCHAR : public ExtensionMethod
{
public:
	GETCHAR()
	: ExtensionMethod(0, "getchar", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		*result = Runtime::Int32Type( getchar() );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
