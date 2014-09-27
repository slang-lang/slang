
#ifndef ObjectiveScript_BluePrint_h
#define ObjectiveScript_BluePrint_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include "RTTI.h"
#include "Token.h"
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class BluePrint : public OSRTTI
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

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

public:
	const std::string& filename() const;

protected:
	Ancestors mAncestors;
	TokenList mTokens;
	Visibility::E mVisibility;

private:
	std::string mFilename;
};

typedef std::list<BluePrint> BluePrintList;


}


#endif
