
#ifndef ObjectiveScript_Attributes_Visibility_h
#define ObjectiveScript_Attributes_Visibility_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Visibility
{
public:
	enum E {
		Private = 0,
		Protected,
		Public
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
