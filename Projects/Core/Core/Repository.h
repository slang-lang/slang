
#ifndef ObjectiveScript_Repository_h
#define ObjectiveScript_Repository_h


// Library includes
#include <map>
#include <string>

// Project includes
#include "Object.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Object;

class Repository
{
public:
	Repository();
	~Repository();

public:
	void addBlueprint(const ObjectBluePrint& object);
	Object createInstance(const std::string& type, const std::string& name);
	bool isAlreadyKnown(const std::string& name) const;

protected:

private:
	typedef std::map<std::string, ObjectBluePrint> BluePrints;

private:
	BluePrints	mBluePrints;
};


}


#endif
