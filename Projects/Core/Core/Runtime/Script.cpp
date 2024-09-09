
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Common/Namespace.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>

// Namespace declarations


namespace Slang {


void Script::execute(Common::ThreadId threadId, const std::string& method, const ParameterList& params, Runtime::Object* result)
{
	MethodSymbol *symbol = Controller::Instance().globalScope()->resolveMethod(method, params, false);
	if ( !symbol ) {
		throw Common::Exceptions::Exception("could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	auto* methodSymbol = dynamic_cast<Common::Method*>(symbol);

	Runtime::ControlFlow::E controlflow = Controller::Instance().thread(threadId)->execute(nullptr, methodSymbol, params, result);

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		Runtime::ExceptionData data = Controller::Instance().thread(threadId)->exception();

		std::string text = "Exception raised in " + data.getPosition().toString() + ":\n";
					text += data.getData()->ToString() + "\n";
					text += data.getStackTrace();

		throw Common::Exceptions::Exception(text);
	}
}

Symbol* Script::resolve(const std::string &symbol)
{
	return Controller::Instance().globalScope()->resolve(symbol);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	return Controller::Instance().globalScope()->resolveMethod(method, params);
}


}
