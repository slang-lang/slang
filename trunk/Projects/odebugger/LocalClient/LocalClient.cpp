
// Header
#include "LocalClient.h"

// Library includes
#include <iostream>

// Project includes
#include <Backend/IBackend.h>

// Namespace declarations


namespace ObjectiveScript {


LocalClient::LocalClient()
: mBackend(0),
  mRunning(false),
  mSettings(0)
{
}

LocalClient::~LocalClient()
{
}

void LocalClient::connectBackend(IBackend* backend)
{
	assert(backend);
	assert(!mBackend);

	mBackend = backend;
}

void LocalClient::connectSettings(Settings* settings)
{
	assert(settings);
	assert(!mSettings);

	mSettings = settings;
}

int LocalClient::exec()
{
	mRunning = true;

	while ( mRunning ) {
		std::string command;

		std::cout << mSettings->prompt() << std::endl;

		getline(std::cin >> std::ws, command);
		std::cin.clear();

		executeCommand(
				parseCommands(command)
		);
	}

	return 0;
}

std::string LocalClient::executeCommand(const StringList &tokens)
{
	StringList::const_iterator it = tokens.begin();

	if ( it != tokens.end() ) {
		std::string cmd = (*it++);

		if ( cmd == "break" || cmd == "b" ) {
			mBackend->addBreakPoint(tokens);
		}
		else if ( cmd == "breakpoints" ) {
			mBackend->printBreakPoints();
		}
		else if ( cmd == "continue" || cmd == "c" ) {
			mBackend->continueExecution();
		}
		else if ( cmd == "delete" || cmd == "d" ) {
			mBackend->removeBreakPoint(tokens);
		}
		else if ( cmd == "execute" || cmd == "e" ) {
			mBackend->executeSymbol(tokens);
		}
		else if ( cmd == "help" ) {
			printHelp();
		}
		else if ( cmd == "into" || cmd == "i" ) {
			mBackend->continueExecution();
		}
		else if ( cmd == "kill" ) {
			mBackend->stop();
		}
		else if ( cmd == "modify" || cmd == "m" ) {
			mBackend->modifySymbol(tokens);
		}
		else if ( cmd == "next" || cmd == "n" ) {
			mBackend->continueExecution();
		}
		else if ( cmd == "out" || cmd == "o" ) {
			mBackend->continueExecution();
		}
		else if ( cmd == "print" || cmd == "p" ) {
			mBackend->printSymbol(tokens);
		}
		else if ( cmd == "quit" || cmd == "q" ) {
			mRunning = false;
		}
		else if ( cmd == "resume" || cmd == "r" ) {
			mBackend->continueExecution();
		}
		else if ( cmd == "run" ) {
			mBackend->run(tokens);
			mBackend->stop();
		}
		else {
			std::cout << "unknown command '" << cmd << "'" << std::endl;
		}
	}

	return "";
}

StringList LocalClient::parseCommands(const std::string& commands) const
{
	StringList params;

	// read in parameters
	unsigned count = 0;
	std::string token;

	while ( count < commands.size() ) {
		char c = commands[count];

		if ( c == ' ' ) {
			if ( !token.empty() ) {
				params.push_back(token);
			}
			token = "";
		}
		else {
			token += c;
		}

		count++;
	}

	// add last token
	if ( !token.empty() ) {
		params.push_back(token);
	}

	return params;
}

void LocalClient::printHelp()
{
	std::cout << "Generic commands:" << std::endl;

	std::cout << "\tbreak (b)" << std::endl;
	std::cout << "\tbreakpoints" << std::endl;
	std::cout << "\tdelete (d)" << std::endl;
	std::cout << "\thelp" << std::endl;
	std::cout << "\tquit (q)" << std::endl;
	std::cout << "\trun" << std::endl;

/*
	if ( mScope ) {
		std::cout << "Debugging commands:" << std::endl;
		std::cout << "\tcontinue (c)" << std::endl;
		std::cout << "\texecute (e)" << std::endl;
		std::cout << "\tinto (i)" << std::endl;
		std::cout << "\tkill" << std::endl;
		std::cout << "\tmodify (m)" << std::endl;
		std::cout << "\tnext (n)" << std::endl;
		std::cout << "\tout (o)" << std::endl;
		std::cout << "\tprint (p)" << std::endl;
		std::cout << "\tresume (r)" << std::endl;
	}
*/
}

std::string LocalClient::read() const
{
	std::string result;

	getline(std::cin >> std::ws, result);
	std::cin.clear();

	return result;
}

void LocalClient::write(const std::string& text)
{
	std::cout << text;
}

void LocalClient::writeln(const std::string& text)
{
	std::cout << text << std::endl;
}


}
