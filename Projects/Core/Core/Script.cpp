
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
: mObject(0),
  mRepository(repository)
{
}

Script::~Script()
{
}

void Script::assign(Runtime::Object *object)
{
	assert(object);
	assert(!mObject);

	mObject = object;
}

Runtime::Object Script::execute(const std::string& method, const ParameterList& params)
{
	MethodSymbol *symbol = mRepository->getGlobalScope()->resolveMethod(method, params, false);
	if ( !symbol ) {
		throw Utils::Exceptions::Exception("Could not resolve method '" + method + "(" + toString(params) + ")'");
	}

	Runtime::Object returnValue;

	Runtime::Method* methodSymbol = static_cast<Runtime::Method*>(symbol);
	Runtime::ControlFlow::E controlflow = methodSymbol->execute(params, &returnValue, TokenIterator());

	if ( controlflow == Runtime::ControlFlow::Throw ) {
		throw Utils::Exceptions::Exception(
			"Exception raised in " + mObject->getFullName() + "::" + mObject->Typename() + "::" + methodSymbol->getName()
		);
	}

	return returnValue;
}

Symbol* Script::resolve(const std::string &symbol)
{
	assert(mObject);

	return mObject->resolve(symbol, false);
}

Symbol* Script::resolveMethod(const std::string &method, const ParameterList &params)
{
	assert(mObject);

	return mObject->resolveMethod(method, params, false);
}


}
