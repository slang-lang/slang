
#ifndef ObjectiveScript_Designtime_BluePrintEnum_h
#define ObjectiveScript_Designtime_BluePrintEnum_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Runtime/AtomicValue.h>
#include <Core/Consts.h>
#include <Core/Symbol.h>
#include "BluePrintGeneric.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


class BluePrintEnum : public BluePrintGeneric
{
public:
	BluePrintEnum();
	BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintEnum();

public:
	IScope* getParent() const;
	void setParent(IScope* parent);

	std::string ToString() const;

protected:

private:
	IScope* mParent;
};


}
}


#endif
