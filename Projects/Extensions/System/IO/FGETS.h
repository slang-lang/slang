
#ifndef Slang_Extensions_System_IO_FGETS_h
#define Slang_Extensions_System_IO_FGETS_h


// Library includes
#include <stdlib.h>

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


class FGETS : public ExtensionMethod
{
	static const int32_t READ_SIZE = 1024;

public:
	FGETS()
	: ExtensionMethod(0, "fgets", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("stream", Designtime::IntegerObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("size", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			auto param_handle = (*it++).value().toInt();
			auto param_size = (*it++).value().toInt();

			if ( mFileHandles.find(param_handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int32_t remainingSize{0};
			while ( remainingSize < param_size ) {
				auto readSize = param_size - remainingSize;
				if ( readSize > READ_SIZE ) {
					readSize = READ_SIZE;
				}

				char stream[READ_SIZE];
				if ( fgets( stream, readSize, mFileHandles[param_handle] ) != nullptr ) {
					*result = Runtime::StringObject( std::string( stream ) );
				}

				remainingSize += readSize;
			}
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
