
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
: mObject(0),
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

		if ( controlflow != Runtime::ControlFlow::Normal ) {
			throw Utils::Exceptions::Exception("Exception raised in " + mObject->getFullName() + "::" + mObject->Typename());
		}
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
	assert(mObject);

	Runtime::Object returnValue;
	try {
		Symbol *symbol = mRepository->getGlobalScope()->resolveMethod(method, params, false);
		if ( !symbol ) {			
			throw Utils::Exceptions::Exception("Could not resolve method '" + method + "(" + toString(params) + ")'");
		}

		Runtime::ControlFlow::E controlflow = static_cast<Runtime::Method*>(symbol)->execute(params, &returnValue, TokenIterator());
		if ( controlflow != Runtime::ControlFlow::Normal ) {
			throw Utils::Exceptions::Exception("Exception raised in " + mObject->getFullName() + "::" + mObject->Typename());
		}
	}
	catch ( std::exception &e ) {
		// catch and log all errors that occurred during execution
		OSerror(e.what());

		throw;
	}

	return returnValue;
}

Symbol* Script::getSymbol(const std::string& symbol)
{
	assert(mObject);

	return mObject->resolve(symbol, false);
}

bool Script::hasMethod(const std::string& m)
{
	assert(mObject);

	if ( mObject->resolve(m, false) ) {
		return true;
	}

	return false;
}

bool Script::hasMethod(const std::string& m, const ParameterList& params)
{
	assert(mObject);

	if ( mObject->resolveMethod(m, params, false) ) {
		return true;
	}

	return false;
}


}
