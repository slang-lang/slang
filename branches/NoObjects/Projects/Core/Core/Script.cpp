
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
: mMemory(0),
  mObject(0),
  mPrinter(0),
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

void Script::connectMemory(Memory *m)
{
	assert(m);
	assert(!mMemory);

	mMemory = m;
}

void Script::connectPrinter(IPrinter *p)
{
	assert(p);
	assert(!mPrinter);

	mPrinter = p;
}

void Script::connectRepository(Repository *r)
{
	assert(r);
	assert(!mRepository);

	mRepository = r;
}

void Script::construct()
{
	try {
		if ( mObject ) {
			mObject->connectPrinter(mPrinter);
			mObject->connectRepository(mRepository);
			mObject->Constructor(ParameterList());
		}
	}
	catch ( Utils::Exception &e ) {
		OSerror(e.what());
	}
}

void Script::destruct()
{
	try {
		mRepository->removeReference(mObject);
	}
	catch ( Utils::Exception &e ) {
		OSerror(e.what());
	}
}

Object Script::execute(const std::string& method, ParameterList params)
{
	OSdebug("execute('" + method /*+ "', [" + toString(params) + "])"*/);

	Object returnValue;
	try {
		assert(mObject);
		returnValue = mObject->execute(method, params);
	}
	catch ( Utils::Exception &e ) {
		OSerror(e.what());
	}

	return returnValue;
}

Object* Script::getMember(const std::string& m)
{
	return mObject->getMember(m);
}

bool Script::hasMember(const std::string& m)
{
	return mObject->hasMember(m);
}

bool Script::hasMethod(const std::string& m)
{
	return mObject->hasMethod(m);
}

bool Script::hasMethod(const std::string& m, const ParameterList& params)
{
	return mObject->hasMethod(m, params);
}


}
