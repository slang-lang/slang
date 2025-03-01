
#ifndef Slang_Extensions_System_SetKeyboardBlockingMode_h
#define Slang_Extensions_System_SetKeyboardBlockingMode_h


// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/BoolType.h>
#include <Core/Designtime/BuildInTypes/StringType.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringType.h>
#include <Core/Tools.h>
#include "System.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {


#ifdef _WIN32
#else
class SetKeyboardBlockingMode : public ExtensionMethod
{
public:
	SetKeyboardBlockingMode()
	: ExtensionMethod(0, "setKeyboardBlocking", Designtime::StringType::TYPENAME, Mutability::Modify)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("mode", Designtime::BoolType::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			bool param_mode = (*it++).value().toBool();

			setKeyboardBlockingMode(param_mode);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Controller::Instance().repository()->createInstance(Runtime::StringType::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringType(std::string(e.what()));

			Controller::Instance().thread(threadId)->exception() = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};
#endif


}
}
}


#endif
