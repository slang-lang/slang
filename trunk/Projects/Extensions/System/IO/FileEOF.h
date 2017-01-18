
#ifndef ObjectiveScript_Extensions_System_IO_FileEOF_h
#define ObjectiveScript_Extensions_System_IO_FileEOF_h


// Library includes
#include <fcntl.h>
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)
#else
#	include <unistd.h>
#endif

// Project includes
#include <Core/BuildInObjects/BoolObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


class FileEOF : public ExtensionMethod
{
public:
	FileEOF()
	: ExtensionMethod(0, "feof", Designtime::BoolObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("handle", Designtime::IntegerObject::TYPENAME));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result, const Token& token)
	{
		Runtime::ControlFlow::E controlFlow = Runtime::ControlFlow::Normal;

		int fileHandle = params.front().value().toInt();

		try {
			*result = Runtime::BoolObject(
				feof(fileHandle)
			);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			Controller::Instance().stack()->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return controlFlow;
	}

};


}
}
}

#endif
