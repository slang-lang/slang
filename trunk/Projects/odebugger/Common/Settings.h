
#ifndef ObjectiveScript_odebugger_Common_Settings_h
#define ObjectiveScript_odebugger_Common_Settings_h


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
		mAutoStart = false;
		mAutoWatch = true;
		mBreakOnException = true;
		mPrompt = "odebugger> ";
	}

public:
	bool autoStart() const {
		return mAutoStart;
	}
	void autoStart(bool value) {
		mAutoStart = value;
	}

	bool autoWatch() const {
		return mAutoWatch;
	}
	void autoWatch(bool value) {
		mAutoWatch = value;
	}

	bool breakOnException() const {
		return mBreakOnException;
	}
	void breakOnException(bool value) {
		mBreakOnException = value;
	}

	const std::string& filename() const {
		return mFilename;
	}
	void filename(const std::string& value) {
		mFilename = value;
	}

	const std::string& prompt() const {
		return mPrompt;
	}
	void prompt(const std::string& value) {
		mPrompt = value;
	}

	const std::string root() const {
		return mRoot;
	}
	void root(const std::string& value) {
		mRoot = value;
	}

private:
	bool mAutoStart;
	bool mAutoWatch;
	bool mBreakOnException;
	std::string mFilename;
	std::string mPrompt;
	std::string mRoot;
};


}


#endif
