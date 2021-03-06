
#ifndef Slang_Extensions_Json_JsonExtension_h
#define Slang_Extensions_Json_JsonExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace Json {


class JsonExtension : public AExtension
{
public:
	JsonExtension();

public:
	void initialize( IScope* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}


#endif
