
#ifndef Slang_Extensions_LIBC_stdio_clearerr_h
#define Slang_Extensions_LIBC_stdio_clearerr_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "stdio.hpp"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace ExtensionLIBC {
namespace stdio {


class CLEARERR : public ExtensionMethod
{
public:
	CLEARERR()
	: ExtensionMethod(0, "clearerr", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("stream", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object */*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_stream = (*it++).value().toInt();

			if ( stdio_t::FileHandles.find(param_stream) == stdio_t::FileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			clearerr( stdio_t::FileHandles[ param_stream ] );
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