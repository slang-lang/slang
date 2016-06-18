
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Runtime/ControlFlow.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Object.h"
#include "Repository.h"

// Namespace declarations


namespace ObjectiveScript {


Script::Script(Repository *repository)
: mRepository(repository)
{
}

Script::~Script()
{
}

void Script::execute(const std::string& method, const ParameterList& params, Runtime::Object* result)
{
	MethodSymbol *symbol = mRepository->getGlobalScope()->resolveMethod(method, params, false);
	if ( !symbol ) {
		throw Utils::Exceptions::Exception("could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	Runtime::Method* methodSymbol = static_cast<Runtime::Method*>(symbol);
	Runtime::ControlFlow::E controlflow = methodSymbol->execute(params, result, Token());

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		throw Utils::Exceptions::Exception("exception raised in method '" + method + "(" + toString(params) + ")'");
	}
}

Symbol* Script::resolve(const std::string &symbol)
{
	return mRepository->getGlobalScope()->resolve(symbol);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	return mRepository->getGlobalScope()->resolveMethod(method, params);
}


}
