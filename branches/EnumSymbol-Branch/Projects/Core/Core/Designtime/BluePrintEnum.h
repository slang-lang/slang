
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


class BluePrintEnum : public BluePrintGeneric,
					  public EnumSymbol
{
public:
	BluePrintEnum();
	BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintEnum();

public:
	virtual ISymbol::IType::E getSymbolType() const;
	virtual const std::string& QualifiedTypename() const;
	virtual const std::string& Typename() const;
	virtual std::string ToString() const;

public:
	IScope* getParent() const;
	void setParent(IScope* parent);

protected:

private:
	IScope* mParent;

private:
	Runtime::AtomicValue getValue() const;
	void setValue(Runtime::AtomicValue value);
	Runtime::AtomicValue mValue;
};

typedef std::list<BluePrintEnum> EnumList;
typedef std::map<std::string, BluePrintEnum> EnumMap;


}
}


#endif
