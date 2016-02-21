
#ifndef ObjectiveScript_Prototype_h
#define ObjectiveScript_Prototype_h


// Library includes
#include <list>

// Project includes
#include <Core/Designtime/BluePrint.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Prototype
{
public:
	Prototype(const Designtime::BluePrint& blue);
	~Prototype();

public:
	Designtime::BluePrint generateBluePrint(const std::string& type);

	const std::string& type() const;

protected:

private:
	Designtime::BluePrint mBluePrint;
};

typedef std::list<Prototype> PrototypeList;


}


#endif
