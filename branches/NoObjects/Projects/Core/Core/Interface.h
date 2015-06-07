
#ifndef ObjectiveScript_Interface_h
#define ObjectiveScript_Interface_h


// Library includes
#include <list>

// Project includes
#include <Core/Attributes/Attributes.h>
#include "RTTI.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Interface : public RTTI,
				  public ObjectAttributes
{
public:
	Interface();
	Interface(const std::string& type, const std::string& filename = "<none>");
	virtual ~Interface();

public:
	const TokenList& getTokens() const;
	void setTokens(const TokenList& tokens);

protected:
	TokenList mTokens;

private:

};

typedef std::list<Interface> InterfaceList;


}


#endif
