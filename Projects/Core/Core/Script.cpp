
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


Script::Script()
: mHasBeenConstructed(false),
  mObject(0),
  mRepository(0)
{
}

Script::~Script()
{
	destruct();
}

void Script::assign(Runtime::Object *object)
{
	assert(object);
	assert(!mObject);

	mObject = object;
}

void Script::connectRepository(Repository *r)
{
	assert(r);
	assert(!mRepository);

	mRepository = r;
}

void Script::construct(const ParameterList& params)
{
	assert(mObject);

	mObject->setRepository(mRepository);

	try {
		Runtime::ControlFlow::E controlflow = mObject->Constructor(params);

		if ( controlflow == Runtime::ControlFlow::Throw ) {
			throw Utils::Exceptions::Exception("Exception raised in " + mObject->getFullName() + "::" + mObject->Typename());
		}

		mHasBeenConstructed = true;
	}
	catch ( std::exception &e ) {
		// catch and log all errors that occurred during execution
		OSerror(e.what());

		throw;
	}
}

void Script::destruct()
{
	try {
		mRepository->removeReference(mObject);
	}
	catch ( std::exception &e ) {
		// catch and log all errors that occurred during execution
		OSerror(e.what());

		throw;
	}
}

Runtime::Object Script::execute(const std::string& method, const ParameterList& params)
{
	Runtime::Object returnValue;
	try {
		Symbol *symbol = mRepository->getGlobalScope()->resolveMethod(method, params, false);
		if ( !symbol ) {			
			throw Utils::Exceptions::Exception("Could not resolve method '" + method + "(" + toString(params) + ")'");
		}

		Runtime::Method* method = static_cast<Runtime::Method*>(symbol);
		Runtime::ControlFlow::E controlflow = method->execute(params, &returnValue, TokenIterator());

		if ( controlflow == Runtime::ControlFlow::Throw ) {
			throw Utils::Exceptions::Exception(
				"Exception raised in " + mObject->getFullName() + "::" + mObject->Typename() + "::" + method->getName()
			);
		}
	}
	catch ( std::exception &e ) {
		// catch and log all errors that occurred during execution
		OSerror(e.what());

		throw;
	}

	return returnValue;
}

bool Script::hasBeenConstructed() const
{
	return mHasBeenConstructed;
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
