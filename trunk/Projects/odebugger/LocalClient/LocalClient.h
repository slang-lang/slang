
#ifndef ObjectiveScript_Debugger_LocalClient_LocalClient_h
#define ObjectiveScript_Debugger_LocalClient_LocalClient_h


// Library includes
#include <string>

// Project includes
#include <Common/Settings.h>
#include <Core/Types.h>
#include <Interfaces/ITerminal.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class IBackend;

class LocalClient : public ITerminal
{
public:
	LocalClient();
	~LocalClient();

public:		// ITerminal implementation
	std::string read() const;
	void write(const std::string& text);
	void writeln(const std::string& text);

public:
	void connectBackend(IBackend* backend);
	void connectSettings(Settings* settings);
	int exec();
	void printHelp();

private:
	std::string executeCommand(const StringList &tokens);
	StringList parseCommands(const std::string& commands) const;

private:
	IBackend* mBackend;
	bool mRunning;
	Settings* mSettings;
};


}


#endif
