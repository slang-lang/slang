
#ifndef ObjectiveScript_Extensions_Apache_Post_h
#define ObjectiveScript_Extensions_Apache_Post_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Apache {


class Post : public ExtensionMethod
{
public:
	Post()
	: ExtensionMethod(0, "post", Designtime::StringObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("name", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList &params, Runtime::Object *result, const Token &token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_name = (*it++).value().toStdString();

			std::string result_value;

			StringMap::const_iterator postIt = mGetQueryString.find(param_name);
			if ( postIt != mPostQueryString.end() ) {
				result_value = postIt->second;
			}

			*result = Runtime::StringObject(result_value);
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

#endif
