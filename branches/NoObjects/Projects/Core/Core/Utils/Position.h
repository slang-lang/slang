
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
	Position(unsigned int l = 0, unsigned int c = 0);

public:
	bool operator==(const Position& other);
	bool operator<(const Position& other);

	std::string toString() const;

public:
	unsigned int line;
	unsigned int column;
};


}
}


#endif
