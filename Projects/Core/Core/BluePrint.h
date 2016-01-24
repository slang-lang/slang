
#ifndef ObjectiveScript_BluePrint_h
#define ObjectiveScript_BluePrint_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Attributes/Visibility.h>
#include "Consts.h"
#include "Interface.h"
#include "RTTI.h"
#include "Scope.h"
#include "Symbol.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Object;
}

namespace Designtime {


class BluePrint : public MethodScope,
				  public BluePrintSymbol,
				  public RTTI
{
public:
	BluePrint();
	BluePrint(const std::string& type, const std::string& filename, const std::string& name = ANONYMOUS_OBJECT);
	virtual ~BluePrint();

public:
	void cleanup();

public:
	const std::string& getName() const;

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

	bool isAbstract() const;

public:
	MethodCollection provideMethods() const {
		return mMethods;
	}
	Symbols provideSymbols() const {
		return mSymbols;
	}

protected:
	const std::string& getTypeName() const {
		return RTTI::Typename();
	}

private:
	std::string mName;
	TokenList mTokens;
	Visibility::E mVisibility;
};

typedef std::list<BluePrint> BluePrintList;


}
}


#endif
