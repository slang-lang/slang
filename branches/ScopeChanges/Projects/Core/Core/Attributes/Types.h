
#ifndef ObjectiveScript_Attributes_Types_h
#define ObjectiveScript_Attributes_Types_h


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



class Algorithm
{
public:
	enum E {
		Unspecified = 0,
		Heuristic,
		Recursive
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class BluePrintType
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


class CheckedExceptions
{
public:
	enum E {
		Unspecified = 0,
		Nothrow,
		Throw
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class ImplementationType
{
public:
	enum E {
		Unspecified = 0,
		Abstract,
		Concrete
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class LanguageFeatureState
{
public:
	enum E {
		Unspecified = 0,
		Deprecated,
		NotImplemented,
		Stable,
		Unstable
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class MemoryLayout
{
public:
	enum E {
		Unspecified = 0,
		Instance,
		Static
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class Mutability
{
public:
	enum E {
		Unknown = 0,
		Const,
		Modify
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class Virtuality
{
public:
	enum E {
		Unknown = 0,
		Abstract,
		Final,
		Virtual
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


}


#endif
