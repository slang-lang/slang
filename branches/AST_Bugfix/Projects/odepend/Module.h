
#ifndef ObjectiveScript_odepend_Module_h
#define ObjectiveScript_odepend_Module_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Module
{
public:
	class Action
	{
	public:
		enum E {
			None,
			Update
		};
	};

public:
	Module(const std::string& name_short, const std::string& remote_version);
	~Module();

public:
	const std::string& getURL() const;
	void setURL(const std::string& url);

public:
	bool operator<(const Module& other) const;

public:
	Action::E mActionNeeded;
	std::string mLocalVersion;
	std::string mLongName;
	std::string mRemoteVersion;
	std::string mShortName;
	std::string mURL;
};


}


#endif
