
#ifndef Slang_Extensions_LIBC_stdio_feof_h
#define Slang_Extensions_LIBC_stdio_feof_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/Int32Type.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class FEOF : public ExtensionMethod
{
public:
	FEOF()
	: ExtensionMethod(0, "feof", Designtime::Int32Type::TYPENAME)
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

		*result = Runtime::Int32Type( feof( stdio_t::FileHandles[ param_stream ] ) );

		return Runtime::ControlFlow::Normal;
	}

};


}
}
}
}


#endif
