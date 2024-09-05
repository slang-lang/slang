
#ifndef Slang_Extensions_System_IO_FFLUSH_h
#define Slang_Extensions_System_IO_FFLUSH_h


// Library includes
#include <cstdlib>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace IO {


class FFLUSH : public ExtensionMethod
{
public:
	FFLUSH()
	: ExtensionMethod(0, "fflush", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("stream", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			auto value = fflush( mFileHandles[ param_handle ] );

			*result = Runtime::IntegerObject( value );
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
