
#ifndef ObjectiveScript_BluePrint_h
#define ObjectiveScript_BluePrint_h


// Library includes
#include <list>
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Visibility.h>
#include "Interface.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class BluePrint : public Interface
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
	BluePrint(const std::string& type, const std::string& filename = "<none>");
	virtual ~BluePrint();

public:
	const Ancestors& getAncestors() const;
	void setAncestors(const Ancestors& ancestors);

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E v);

protected:
	Ancestors mAncestors;
	Visibility::E mVisibility;

private:

};

typedef std::list<BluePrint> BluePrintList;


}


#endif
