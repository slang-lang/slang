
#ifndef Printer_h
#define Printer_h


// Library includes

// Project includes
#include <Core/Interfaces/IPrinter.h>
#include <Interfaces/Common/ILogger.h>

// Forward declarations

// Namespace declarations


class Printer : public ObjectiveScript::IPrinter
{
public:
	Printer(Utils::Common::ILogger *l)
	: mLogger(l)
	{ }

public:
	void log(const std::string& text) {
		mLogger->LogDebug(text, 0, 0);
	}

	void print(const std::string& text) {
		std::cout << text;// << std::endl;
	}

private:
	Utils::Common::ILogger *mLogger;
};


#endif
