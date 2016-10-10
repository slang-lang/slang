
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Runtime/ControlFlow.h>
#include <Utils.h>
#include "Interpreter.h"
#include "Object.h"
#include "Scope.h"

// Namespace declarations


namespace ObjectiveScript {


Script::Script(MethodScope* scope)
: mScope(scope)
{
}

Script::~Script()
{
}

void Script::execute(const std::string& method, const ParameterList& params, Runtime::Object* result)
{
	MethodSymbol *symbol = mScope->resolveMethod(method, params, false);
	if ( !symbol ) {
		throw Common::Exceptions::Exception("could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	Runtime::Method* methodSymbol = static_cast<Runtime::Method*>(symbol);

	Runtime::Interpreter interpreter;
	Runtime::ControlFlow::E controlflow = interpreter.execute(methodSymbol, params, result);

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		//Runtime::Object* data = methodSymbol->getExceptionData().getData();
		//Common::Position position = methodSymbol->getExceptionData().getPosition();

		Runtime::Object* data = interpreter.getExceptionData().getData();

		std::string text = "Exception raised in method '" + method + "(" + toString(params) + ")':\n";
					text += data->getValue().toStdString();

		throw Common::Exceptions::Exception(text);
	}
}

Symbol* Script::resolve(const std::string &symbol)
{
	return mScope->resolve(symbol);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	return mScope->resolveMethod(method, params);
}


}
