
#ifndef Slang_Extensions_System_IO_FileOpen_h
#define Slang_Extensions_System_IO_FileOpen_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/IntegerObject.h>
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


class FileOpen : public ExtensionMethod
{
public:
	FileOpen()
	: ExtensionMethod(0, "fopen", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("filename", Designtime::StringObject::TYPENAME));
		params.push_back(Parameter::CreateDesigntime("accessmode", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_filename = (*it++).value().toStdString();
			std::string param_accessmode = (*it++).value().toStdString();

			int result_handle = 0;

			FILE* fileHandle = fopen(param_filename.c_str(), param_accessmode.c_str());
			if ( fileHandle ) {
				result_handle = mFileHandles.size() + 1;

				mFileHandles.insert(std::make_pair(result_handle, fileHandle));
			}

			*result = Runtime::IntegerObject(result_handle);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}

private:
	int parseAccessMode(std::string accessmode) const
	{
		int mode = 0;

		while ( accessmode.size() > 0 ) {
			switch ( accessmode[0] ) {
				case 'a': mode |= O_APPEND; break;
				case 'c': mode |= O_CREAT; break;
				case 'r': mode |= O_RDONLY; break;
				case 't': mode |= O_TRUNC; break;
				case 'w': mode |= O_WRONLY; break;
				case 'x': mode |= O_EXCL; break;
				default: break;
			}

			accessmode = accessmode.substr(1, accessmode.size());
		}

		return mode;
	}
};


}
}
}
}


#endif
