
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes
#include <array>
#include <stdexcept>
#ifdef _WIN32
#else
#	include <termios.h>
#	include <stdlib.h>
#endif

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/Exceptions.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {

#ifdef _WIN32
#else
extern void restoreKeyboardBlockingMode();
extern void setKeyboardBlockingMode(bool blocking);
extern void storeKeyboardBlockingMode();
#endif


class SystemExecute : public ExtensionMethod
{
public:
	SystemExecute()
	: ExtensionMethod(0, "system", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("command", Designtime::StringObject::TYPENAME, VALUE_NONE, true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_text = (*it++).value().toStdString();

#if __cplusplus >= 201402L
			std::array<char, 128> buffer;
			std::string resultStr;
			std::shared_ptr<FILE> pipe(popen(param_text.c_str(), "r"), pclose);
			if ( !pipe ) {
				throw std::runtime_error("popen() failed!");
			}

			while ( !feof(pipe.get()) ) {
				if ( fgets(buffer.data(), 128, pipe.get()) != NULL ) {
					resultStr += buffer.data();
				}
			}
#else
			std::string resultStr = "";

			FILE* pipe = popen(param_text.c_str(), "r");
			if ( !pipe ) {
				throw std::runtime_error("popen() failed!");
			}

			try {
				char buffer[128];

				while ( !feof(pipe) ) {
					if ( fgets(buffer, 128, pipe) != NULL ) {
						resultStr += buffer;
					}
				}
			}
			catch ( ... ) {
				pclose(pipe);
				throw;
			}
			pclose(pipe);
#endif

			*result = Runtime::StringObject(resultStr);
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


#endif
