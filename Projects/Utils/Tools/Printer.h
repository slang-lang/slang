
#ifndef _Utils_Tools_Printer_h_
#define _Utils_Tools_Printer_h_


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {


class Printer
{
public:
	static Printer* Instance() {
		static Printer mPrinter;

		return &mPrinter;
	}

public:
	void activateFileAndLinePrinting(bool state);
	void activatePrinter(bool state);

public:
	void print(const std::string& text, const std::string& file = "", int line = 0) const;
	void println(const std::string& text, const std::string& file = "", int line = 0);

public:
	bool ActivatePrinter;
	bool AutomaticLineBreak;
	bool PrintFileAndLine;

private:
	Printer();
};


}


#endif
