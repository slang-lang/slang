
#ifndef ObjectiveScript_Designtime_BluePrintGeneric_h
#define ObjectiveScript_Designtime_BluePrintGeneric_h


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


class BluePrintGeneric : public ISymbol
{
public:
	BluePrintGeneric();
	BluePrintGeneric(const std::string& type, const std::string& filename);
	virtual ~BluePrintGeneric();

public:
	virtual void cleanup();

public:
	void setQualifiedTypename(const std::string& name);

	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

protected:
	std::string mFilename;
	std::string mQualifiedTypename;
	TokenList mTokens;
	std::string mTypename;

private:
};


}
}


#endif
