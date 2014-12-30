
#ifndef ObjectiveScript_Utils_Position_h
#define ObjectiveScript_Utils_Position_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Utils {


class Position
{
public:
	Position(size_t l = 0, size_t c = 0);

public:
	bool operator==(const Position& other);
	bool operator<(const Position& other);

public:
	size_t line;
	size_t column;
};


}
}


#endif
