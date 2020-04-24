
#ifndef Slang_slang_dbg_Backend_Watch_h
#define Slang_slang_dbg_Backend_Watch_h


// Library includes
#include <set>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {


class Watch
{
public:
	Watch();
	Watch(const std::string& symbol);
	~Watch();

public:
	const std::string& symbol() const;

	std::string toString() const;

	const std::string& value() const;
	void value(const std::string& v);

public:
	bool operator<(const Watch& other) const;
	bool operator==(const Watch& other) const;

private:
	std::string mSymbol;
	std::string mValue;
};


typedef std::set<Watch> WatchCollection;


}


#endif
