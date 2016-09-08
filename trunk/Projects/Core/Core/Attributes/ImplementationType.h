
#ifndef ObjectiveScript_Attributes_ImplementationType_h
#define ObjectiveScript_Attributes_ImplementationType_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class ImplementationType
{
public:
	enum E {
		Unknown = 0,
		Abstract,
		FullyImplemented,
		Interface
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
