
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
	Printer();

public:
	void activateFileAndLinePrinting(bool state);
	void activatePrinter(bool state);

public:
	void print(const std::string& text, const std::string& file = "", int line = 0);
	void println(const std::string& text, const std::string& file = "", int line = 0);

public:
	bool ActivatePrinter;
	bool AutomaticLineBreak;
	bool PrintFileAndLine;
};


class PrinterDriver
{
public:
	static Printer& getInstance() {
		static Printer mPrinter;

		return mPrinter;
	}

private:
	PrinterDriver();
	PrinterDriver(const PrinterDriver& );
	PrinterDriver operator=(const PrinterDriver& );
	~PrinterDriver();
};


}


#endif
