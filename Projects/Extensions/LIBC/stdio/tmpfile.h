
#ifndef Slang_Extensions_LIBC_stdio_tmpfile_h
#define Slang_Extensions_LIBC_stdio_tmpfile_h


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
#include <Core/Designtime/BuildInTypes/VoidType.h>
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


class TMPFILE : public ExtensionMethod
{
public:
	TMPFILE()
	: ExtensionMethod(0, "tmpfile", Designtime::VoidType::TYPENAME)
	{
		ParameterList params;

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		int result_handle = 0;

		FILE* fileHandle = tmpfile();
		if ( fileHandle ) {
			result_handle = stdio_t::FileHandles.size();

			stdio_t::FileHandles.insert(std::make_pair(result_handle, fileHandle));
		}

		*result = Runtime::Int32Type( result_handle );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
