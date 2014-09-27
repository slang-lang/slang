
// Header
#include "Script.h"

// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include "Exceptions.h"
#include "Object.h"
#include "Tools.h"

// Namespace declarations


namespace ObjectiveScript {


Script::Script(size_t id)
: mId(id),
  mObject(0),
  mPrinter(0),
  mRepository(0)
{
}

Script::~Script()
{
}

void Script::assign(Object *object)
{
	assert(object);
	mObject = object;
}

void Script::connectPrinter(IPrinter *p)
{
	assert(p);
	assert(!mPrinter);

	mPrinter = p;
}

void Script::construct()
{
	try {
		if ( mObject ) {
			mObject->connectPrinter(mPrinter);
			mObject->Constructor(VariablesList());
		}
	}
	catch ( Exception &e ) {
		OSerror(e.what());
	}
}

void Script::destruct()
{
	try {
		if ( mObject ) {
			mObject->Destructor();
		}
	}
	catch ( Exception &e ) {
		OSerror(e.what());
	}
}

Object Script::execute(const std::string& method, VariablesList params)
{
	OSdebug("execute('" + method + "', [" + toString(params) + "])");

	Object returnValue;
	try {
		assert(mObject);
		returnValue = mObject->execute(method, params);
	}
	catch ( Exception &e ) {
		OSerror(e.what());
	}

	return returnValue;
}

Object& Script::getMember(const std::string& m)
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

bool Script::hasMethod(const std::string& m, const VariablesList& params)
{
	return mObject->hasMethod(m, params);
}

void Script::init(Repository *r)
{
	OSdebug("initialize");

	mRepository = r;

	if ( mObject ) {
		mObject->connectRepository(mRepository);
	}
}


}
