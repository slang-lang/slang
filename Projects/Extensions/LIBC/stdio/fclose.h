
#ifndef Slang_Extensions_LIBC_stdio_fclose_h
#define Slang_Extensions_LIBC_stdio_fclose_h


// Library includes

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


class FCLOSE : public ExtensionMethod
{
public:
	FCLOSE()
	: ExtensionMethod(0, "fclose", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::Int32Type::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_handle = (*it++).value().toInt();

		if ( stdio_t::FileHandles.find(param_handle) == stdio_t::FileHandles.end() ) {
			throw Runtime::Exceptions::RuntimeException("invalid file handle");
		}

		int fileResult = fclose(stdio_t::FileHandles[param_handle]);
		if ( fileResult == -1 ) {
			throw Runtime::Exceptions::RuntimeException("invalid file handle");
		}

		*result = Runtime::Int32Type(fileResult);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
