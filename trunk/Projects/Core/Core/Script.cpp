
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include <Core/Utils/Exceptions.h>
#include <Core/Utils/Utils.h>
#include "Object.h"
#include "Repository.h"
#include "Tools.h"

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
	if ( !mObject ) {
		throw Utils::Exceptions::Exception("no object assigned");
	}

	mObject->connectRepository(mRepository);
	mObject->Constructor(params);
}

void Script::destruct()
{
	try {
		mRepository->removeReference(mObject);
	}
	catch ( Utils::Exceptions::Exception &e ) {
		OSerror(e.what());
	}
}

Object Script::execute(const std::string& method, const ParameterList& params)
{
	Object returnValue;
	try {
		if ( !mObject ) {
			throw Utils::Exceptions::Exception("no object assigned");
		}

		mObject->execute(&returnValue, method, params);
	}
	catch ( Utils::Exceptions::Exception &e ) {
		OSerror(e.what());
	}

	return returnValue;
}

Object* Script::getMember(const std::string& m)
{
	if ( !mObject ) {
		throw Utils::Exceptions::Exception("no object assigned");
	}

	return mObject->getMember(m);
}

bool Script::hasMethod(const std::string& m)
{
	if ( !mObject ) {
		throw Utils::Exceptions::Exception("no object assigned");
	}

	return mObject->hasMethod(m);
}

bool Script::hasMethod(const std::string& m, const ParameterList& params)
{
	if ( !mObject ) {
		throw Utils::Exceptions::Exception("no object assigned");
	}

	return mObject->hasMethod(m, params);
}


}
