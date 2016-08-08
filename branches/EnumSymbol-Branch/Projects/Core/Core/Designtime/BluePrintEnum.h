
#ifndef ObjectiveScript_Designtime_BluePrintEnum_h
#define ObjectiveScript_Designtime_BluePrintEnum_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Attributes/Visibility.h>
#include <Core/Runtime/AtomicValue.h>
#include <Core/Consts.h>
#include <Core/Scope.h>
#include <Core/Symbol.h>
#include <Core/Types.h>
#include "Ancestor.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Designtime {


// TODO: derive BluePrintEnum from BluePrintGeneric

class BluePrintEnum : public EnumSymbol
{
public:
	BluePrintEnum();
	BluePrintEnum(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrintEnum();

public:
	const std::string& QualifiedTypename() const { return mQualifiedTypeName; }
	const std::string& Typename() const { return mTypename; }

public:
	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

	IScope* getParent() const;
	void setParent(IScope* parent);

	void setQualifiedTypename(const std::string& name);

	virtual std::string ToString() const;

protected:

private:
	std::string mFilename;
	IScope *mParent;
	std::string mQualifiedTypeName;
	TokenList mTokens;
	std::string mTypename;
	Visibility::E mVisibility;

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
