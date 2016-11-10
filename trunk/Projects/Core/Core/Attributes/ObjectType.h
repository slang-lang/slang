
#ifndef ObjectiveScript_Attributes_ObjectType_h
#define ObjectiveScript_Attributes_ObjectType_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class ObjectType
{
public:
	enum E {
		Unknown = 0,
		Enum,
		Interface,
		Object
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
