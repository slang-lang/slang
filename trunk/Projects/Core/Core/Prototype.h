
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
	Prototype(const DesignTime::BluePrint& blue);
	~Prototype();

public:
	DesignTime::BluePrint generateBluePrint(const std::string& type);

	const std::string& type() const;

protected:

private:
	DesignTime::BluePrint mBluePrint;
};

typedef std::list<Prototype> PrototypeList;


}


#endif
