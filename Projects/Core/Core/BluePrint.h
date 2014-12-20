
#ifndef ObjectiveScript_BluePrint_h
#define ObjectiveScript_BluePrint_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Visibility.h>
#include "RTTI.h"
#include "Token.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class BluePrint : public RTTI
{
public:
	class Ancestor
	{
	public:
		Ancestor()
		: mName(""),
		  mVisibility(Visibility::Private)
		{ }

		Ancestor(const std::string& name, Visibility::E visibility)
		: mName(name),
		  mVisibility(visibility)
		{ }

	public:
		const std::string& name() const {
			return mName;
		}
		Visibility::E visibility() const {
			return mVisibility;
		}

	protected:

	private:
		std::string	mName;
		Visibility::E mVisibility;
	};

	typedef std::map<std::string, Ancestor> Ancestors;

public:
	BluePrint();
	BluePrint(const std::string& type, const std::string& filename);
	virtual ~BluePrint();

public:
	const Ancestors& getAncestors() const;
	void setAncestors(const Ancestors& ancestors);

	const TokenList& getTokens() const;
	virtual void setTokens(const TokenList& tokens);

	Visibility::E getAncestorVisibility() const;
	void setAncestorVisibility(Visibility::E v);

protected:
	Ancestors mAncestors;
	TokenList mTokens;
	Visibility::E mVisibility;

private:

};

typedef std::list<BluePrint> BluePrintList;


}


#endif
