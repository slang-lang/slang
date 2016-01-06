
#ifndef ObjectiveScript_Utils_Position_h
#define ObjectiveScript_Utils_Position_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


class Position
{
public:
	Position(const std::string& f = "", unsigned int l = 0, unsigned int c = 0);

public:
	bool operator==(const Position& other) const;
	bool operator<(const Position& other) const;

	std::string toString() const;

public:
	std::string file;
	unsigned int line;
	unsigned int column;
};


}
}


#endif
