
#ifndef Slang_Extensions_System_System_h
#define Slang_Extensions_System_System_h


// Library includes
#include <stdexcept>
#ifdef _WIN32
#	include <stdio.h>
#	include <cstdlib>
#else
#	include <termios.h>
#	include <cstdlib>
#endif

// Project includes
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Designtime/BuildInTypes/VoidType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>

// Forward declarations

// Namespace declarations


namespace Slang {
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
	: ExtensionMethod(0, "system", Designtime::StringType::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("command", Designtime::StringType::TYPENAME, Runtime::AtomicValue(std::string(VALUE_NONE)), true));

		setSignature(params);
	}

	Runtime::ControlFlow::E execute( const ParameterList& params, Runtime::Object* result )
	{
		ParameterList list = mergeParameters(params);

		ParameterList::const_iterator it = list.begin();

		std::string param_text = (*it++).value().toStdString();

#if __cplusplus > 201402L
		std::array<char, 128> buffer;
		std::string resultStr;
		std::shared_ptr<FILE> pipe(popen(param_text.c_str(), "r"), pclose);
		if ( !pipe ) {
			throw std::runtime_error("popen() failed!");
		}

		while ( !feof(pipe.get()) ) {
			if ( fgets(buffer.data(), 128, pipe.get()) != nullptr ) {
				resultStr += buffer.data();
			}
		}
#else
		std::string resultStr = "";

#ifdef _WIN32
		FILE* pipe = _popen(param_text.c_str(), "r");
#else
		FILE* pipe = popen(param_text.c_str(), "r");
#endif
		if ( !pipe ) {
			throw std::runtime_error("popen() failed!");
		}

		try {
			char buffer[128];

			while ( !feof(pipe) ) {
				if ( fgets(buffer, 128, pipe) != nullptr ) {
					resultStr += buffer;
				}
			}
		}
		catch ( ... ) {
#ifdef _WIN32
			_pclose(pipe);
#else
			pclose(pipe);
#endif
			throw;
		}
#ifdef _WIN32
		_pclose(pipe);
#else
		pclose(pipe);
#endif
#endif

		*result = Runtime::StringType(resultStr);

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}


#endif
