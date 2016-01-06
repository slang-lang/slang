
// Header
#include "Script.h"

// Library includes

// Project includes
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

void Script::assign(Object *object)
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

	mObject->connectRepository(mRepository);

	try {
		mObject->Constructor(params);
	}
	catch ( Utils::Exceptions::Exception &e ) {
		// catch and log all errors that occurred during method execution
		OSerror(e.what());

		throw;
	}
}

void Script::destruct()
{
	assert(mObject);

	try {
		mRepository->removeReference(mObject);
	}
	catch ( Utils::Exceptions::Exception &e ) {
		OSerror(e.what());

		throw;
	}
}

Object Script::execute(const std::string& method, const ParameterList& params)
{
	assert(mObject);

	Object returnValue;
	try {
		mObject->execute(&returnValue, method, params);
	}
	catch ( Utils::Exceptions::Exception &e ) {
		OSerror(e.what());

		throw;
	}

	return returnValue;
}

Object* Script::getMember(const std::string& m)
{
	assert(mObject);

	return mObject->getMember(m);
}

bool Script::hasMethod(const std::string& m)
{
	assert(mObject);

	return mObject->hasMethod(m);
}

bool Script::hasMethod(const std::string& m, const ParameterList& params)
{
	assert(mObject);

	return mObject->hasMethod(m, params);
}


}
