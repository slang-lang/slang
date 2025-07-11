
#ifndef Slang_slang_dbg_Interfaces_ITerminal_h
#define Slang_slang_dbg_Interfaces_ITerminal_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {


class ITerminal
{
public:
	virtual ~ITerminal() = default;

	virtual std::string read() = 0;
	virtual void write( const std::string& text ) = 0;
	virtual void writeln( const std::string& text ) = 0;
};


}


#endif Slang_slang_dbg_Interfaces_ITerminal_h
