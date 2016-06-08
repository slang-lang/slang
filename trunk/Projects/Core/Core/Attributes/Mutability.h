
#ifndef ObjectiveScript_Attributes_Mutability_h
#define ObjectiveScript_Attributes_Mutability_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Mutability
{
public:
	enum E {
		Unknown = 0,
		Const,
		Final,
		Modify
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
