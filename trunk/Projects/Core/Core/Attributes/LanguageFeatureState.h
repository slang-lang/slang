
#ifndef ObjectiveScript_Attributes_LanguageFeatureState_h
#define ObjectiveScript_Attributes_LanguageFeatureState_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


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


}


#endif
