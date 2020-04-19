
#ifndef Slang_Core_Core_Common_Position_h
#define Slang_Core_Core_Common_Position_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Common {


class Position
{
public:
	Position(const std::string& file = "", unsigned int line = 0, unsigned int column = 0);

public:
	bool operator==(const Position& other) const;
	bool operator<(const Position& other) const;

	std::string toString() const;

public:
	std::string mFile;
	unsigned int mLine;
	unsigned int mColumn;
};


}
}


#endif
