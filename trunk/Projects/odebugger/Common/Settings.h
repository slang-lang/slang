
#ifndef ObjectiveScript_Debugger_Common_Settings_h
#define ObjectiveScript_Debugger_Common_Settings_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Settings
{
public:
	Settings()
	{
		mPrompt = "odebugger> ";
	}

public:
	const std::string& filename() const {
		return mFilename;
	}
	void filename(const std::string& file) {
		mFilename = file;
	}

	const std::string& prompt() const {
		return mPrompt;
	}

	const std::string root() const {
		return mRoot;
	}
	void root(const std::string& r) {
		mRoot = r;
	}

private:
	std::string mFilename;
	std::string mPrompt;
	std::string mRoot;
};


}


#endif
