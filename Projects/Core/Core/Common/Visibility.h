
#ifndef Slang_Core_Core_Common_Visibility_h
#define Slang_Core_Core_Common_Visibility_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace Slang {


class Visibility
{
public:
	enum E {
		Designtime = 0,
		Private,
		Protected,
		Public
	};

	static E convert(const std::string& v);
	static std::string convert(E e);

private:
	static const std::string DesigntimeStr;
	static const std::string PrivateStr;
	static const std::string ProtectedStr;
	static const std::string PublicStr;
};


}


#endif
