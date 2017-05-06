
#ifndef ObjectiveScript_Extensions_System_IO_FileClose_h
#define ObjectiveScript_Extensions_System_IO_FileClose_h


// Library includes

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>
#include "Defines.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace IO {


class FileClose : public ExtensionMethod
{
public:
	FileClose()
	: ExtensionMethod(0, "fclose", Designtime::IntegerObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_handle = (*it++).value().toStdString();

			int handle = Utils::Tools::stringToInt(param_handle);
			if ( mFileHandles.find(handle) == mFileHandles.end() ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			int fileResult = fclose(mFileHandles[handle]);
			if ( fileResult == -1 ) {
				throw Runtime::Exceptions::RuntimeException("invalid file handle");
			}

			*result = Runtime::IntegerObject(fileResult);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
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
