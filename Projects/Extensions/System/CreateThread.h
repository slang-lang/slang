
#ifndef ObjectiveScript_Extensions_System_CreateThread_h
#define ObjectiveScript_Extensions_System_CreateThread_h


// Library includes
#include <stdlib.h>

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Runtime/BuildInTypes/StringObject.h>
#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {


class CreateThread : public ExtensionMethod
{
public:
	CreateThread()
	: ExtensionMethod(0, "createThread", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter::CreateDesigntime("thread", Common::TypeDeclaration("Thread")));
		//params.push_back(Parameter::CreateDesigntime("thread", Common::TypeDeclaration("Thread"), Runtime::AtomicValue(), false, Mutability::Const, AccessMode::ByReference));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(Common::ThreadId threadId, const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			Runtime::Reference param_thread = (*it++).reference();
			if ( param_thread == Runtime::NullReference ) {
				return Runtime::ControlFlow::Normal;
			}

			Runtime::Object* threadObject = Controller::Instance().memory()->get(param_thread);
			Common::Method* threadMethod = dynamic_cast<Common::Method*>(threadObject->resolveMethod("start", ParameterList(), false, Visibility::Public));

			Thread* thread = Controller::Instance().threads()->createThread();
			thread->execute(threadObject, threadMethod, ParameterList(), NULL);
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
