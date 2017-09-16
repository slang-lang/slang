
#ifndef ObjectiveScript_Attributes_AccessMode_h
#define ObjectiveScript_Attributes_AccessMode_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class AccessMode
{
public:
	enum E {
		Unspecified = 0,
		ByReference,
		ByValue
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
