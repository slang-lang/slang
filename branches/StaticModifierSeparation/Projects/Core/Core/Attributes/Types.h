
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


class ImplementationType
{
public:
	enum E {
		Unknown = 0,
		Abstract,
		ForwardDeclaration,
		FullyImplemented,
		Interface
	};

	static E convert(const std::string& v);
	static std::string convert(E e);
};


class LanguageFeatureState
{
public:
	enum E {
		Unknown = 0,
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
		Unknown = 0,
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
