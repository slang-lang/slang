
#ifndef Slang_Extensions_LIBC_stdio_putchar_h
#define Slang_Extensions_LIBC_stdio_putchar_h


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
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class PUTCHAR : public ExtensionMethod
{
public:
	PUTCHAR()
	: ExtensionMethod(0, "putchar", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("ch", Designtime::Int32Type::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_ch = (*it++).value().toInt();

		*result = Runtime::Int32Type( putchar( param_ch ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
