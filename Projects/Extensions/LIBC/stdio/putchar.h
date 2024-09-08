
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
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
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


class PUTCHAR : public ExtensionMethod
{
public:
	PUTCHAR()
	: ExtensionMethod(0, "putchar", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("ch", Designtime::IntegerObject::TYPENAME, 0));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
            ParameterList::const_iterator it = list.begin();

            auto param_ch = (*it++).value().toInt();

            *result = Runtime::IntegerObject( putchar( param_ch ) );
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
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
