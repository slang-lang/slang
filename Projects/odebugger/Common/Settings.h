
#ifndef ObjectiveScript_odebugger_Common_Settings_h
#define ObjectiveScript_odebugger_Common_Settings_h


// Library includes
#include <string>

// Project includes
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Settings
{
public:
	Settings()
	{
		mAutoStart = false;
		mAutoStop = false;
		mAutoWatch = true;
		mBreakOnExceptionCatch = true;
		mBreakOnExceptionThrow = true;
		mPrompt = "odebugger> ";
		mRemoteClient = false;
	}

public:
	bool autoStart() const {
		return mAutoStart;
	}
	void autoStart(bool value) {
		mAutoStart = value;
	}

	bool autoStop() const {
		return mAutoStop;
	}
	void autoStop(bool value) {
		mAutoStop = value;
	}

	bool autoWatch() const {
		return mAutoWatch;
	}
	void autoWatch(bool value) {
		mAutoWatch = value;
	}

	bool breakOnExceptionCatch() const {
		return mBreakOnExceptionCatch;
	}
	void breakOnExceptionCatch(bool value) {
		mBreakOnExceptionCatch = value;
	}

	bool breakOnExceptionThrow() const {
		return mBreakOnExceptionThrow;
	}
	void breakOnExceptionThrow(bool value) {
		mBreakOnExceptionThrow = value;
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

	bool remoteClient() const {
		return mRemoteClient;
	}
	void remoteClient(bool value) {
		mRemoteClient = value;
	}

	const StringSet& libraryFolders() const {
		return mLibraryFolders;
	}
	void addLibraryFolder(const std::string& value) {
		mLibraryFolders.insert(value);
	}

private:
	bool mAutoStart;
	bool mAutoStop;
	bool mAutoWatch;
	bool mBreakOnExceptionCatch;
	bool mBreakOnExceptionThrow;
	std::string mFilename;
	StringSet mLibraryFolders;
	std::string mPrompt;
	bool mRemoteClient;
};


}


#endif
