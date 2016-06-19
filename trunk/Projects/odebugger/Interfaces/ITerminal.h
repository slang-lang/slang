
#ifndef ObjectiveScript_Debugger_Interfaces_ITerminal_h
#define ObjectiveScript_Debugger_Interfaces_ITerminal_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class ITerminal
{
public:
	virtual ~ITerminal() { }

	virtual std::string read() const = 0;
	virtual void write(const std::string& text) = 0;
	virtual void writeln(const std::string& text) = 0;
};


}


#endif
