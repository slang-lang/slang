
#ifndef ObjectiveScript_Designtime_Prototype_h
#define ObjectiveScript_Designtime_Prototype_h


// Library includes
#include <list>
#include <map>

// Project includes
#include <Core/Designtime/BluePrintObject.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class Prototype
{
public:
	Prototype(const Designtime::BluePrintObject& blue);
	~Prototype();

public:
	Designtime::BluePrintObject generateBluePrint(const std::string& type);

	const std::string& type() const;

protected:

private:
	Designtime::BluePrintObject mBluePrint;
};

typedef std::list<Prototype> PrototypeList;
typedef std::map<std::string, Prototype> PrototypeMap;


}
}


#endif
