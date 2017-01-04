
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Common/Method.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/VirtualMachine/Controller.h>
#include <Utils.h>

// Namespace declarations


namespace ObjectiveScript {


Script::Script()
{
}

Script::~Script()
{
}

void Script::execute(const std::string& method, const ParameterList& params, Runtime::Object* result)
{
	MethodSymbol *symbol = Controller::Instance().stack()->globalScope()->resolveMethod(method, params, false);
	if ( !symbol ) {
		throw Common::Exceptions::Exception("could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	Common::Method* methodSymbol = static_cast<Common::Method*>(symbol);

	Runtime::Interpreter interpreter;
	Runtime::ControlFlow::E controlflow = interpreter.execute(methodSymbol, params, result);

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		Runtime::ExceptionData data = Controller::Instance().stack()->exception();

		std::string text = "Exception raised in " + data.getPosition().toString() + ":\n";
					text += data.getData()->ToString();

		throw Common::Exceptions::Exception(text);
	}
}

Symbol* Script::resolve(const std::string &symbol)
{
	return Controller::Instance().stack()->globalScope()->resolve(symbol);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	return Controller::Instance().stack()->globalScope()->resolveMethod(method, params);
}


}
