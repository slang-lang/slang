
#ifndef ObjectiveScript_Prototype_h
#define ObjectiveScript_Prototype_h


// Library includes
#include <list>

// Project includes
#include "BluePrint.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Prototype
{
public:
	Prototype(const BluePrint& blue);
	~Prototype();

public:
	BluePrint generateBluePrint(const std::string& type);

	const std::string& type() const;

protected:

private:
	BluePrint mBluePrint;
};

typedef std::list<Prototype> PrototypeList;


}


#endif