
#ifndef Slang_Extensions_System_CreateInstance_h
#define Slang_Extensions_System_CreateInstance_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Designtime/BuildInTypes/UserObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Runtime/BuildInTypes/UserObject.h>
#include <Core/Tools.h>
#include <Core/VirtualMachine/Controller.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Reflection {


class CreateInstance : public ExtensionMethod
{
public:
	CreateInstance()
	: ExtensionMethod(0, "createInstance", Designtime::UserObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("type", Designtime::StringObject::TYPENAME));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* result, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			std::string param_type = (*it++).value().toStdString();

			Runtime::Object* newInstance = Controller::Instance().repository()->createReference(param_type, ANONYMOUS_OBJECT, PrototypeConstraints(), Repository::InitilizationType::Final);

			*result = *newInstance;
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
