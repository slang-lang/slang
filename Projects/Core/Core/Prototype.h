
#ifndef ObjectiveScript_Prototype_h
#define ObjectiveScript_Prototype_h


// Library includes
#include <list>

// Project includes
#include "Object.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Prototype
{
public:
	Prototype(const ObjectBluePrint& blue);
	~Prototype();

public:
	ObjectBluePrint generateBluePrint(const std::string& type);

	const std::string& type() const;

protected:

private:
	ObjectBluePrint mBluePrint;
};

typedef std::list<Prototype> PrototypeList;


}


#endif
