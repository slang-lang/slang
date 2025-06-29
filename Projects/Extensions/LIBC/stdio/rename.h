
#ifndef Slang_Extensions_LIBC_stdio_rename_h
#define Slang_Extensions_LIBC_stdio_rename_h


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
#include <Core/Runtime/BuildInTypes/Int32Type.h>
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


class RENAME : public ExtensionMethod
{
public:
	RENAME()
	: ExtensionMethod(0, "rename", Designtime::Int32Type::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("old_filename", Designtime::StringType::TYPENAME, 0));
		params.push_back(Parameter::CreateDesigntime("new_filename", Designtime::StringType::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList &params, Runtime::Object *result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		auto param_old_filename = (*it++).value().toStdString();
		auto param_new_filename = (*it++).value().toStdString();

		*result = Runtime::Int32Type( rename( param_old_filename.c_str(), param_new_filename.c_str() ) );

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
