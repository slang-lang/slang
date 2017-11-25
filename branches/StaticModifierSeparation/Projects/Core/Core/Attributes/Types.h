
#ifndef ObjectiveScript_Attributes_Types_h
#define ObjectiveScript_Attributes_Types_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class MemoryLayout
{
public:
	enum E {
		Unknown = 0,
		Instance,
		Static
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class Virtuality
{
public:
	enum E {
		Unknown = 0,
		Final,
		Virtual
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
