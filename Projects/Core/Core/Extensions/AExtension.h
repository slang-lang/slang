
#ifndef Slang_Core_Core_Extensions_AExtension_h
#define Slang_Core_Core_Extensions_AExtension_h


// Library includes
#include <list>
#include <string>
#include <utility>

// Project includes
#include "ExtensionMethod.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class IScope;

}

class AExtension
{
public:
	AExtension(std::string name)
	: mName(std::move(name))
	{ }
	virtual ~AExtension() = default;

public:
	virtual void initialize(Slang::IScope* scope) = 0;
	virtual void provideMethods(Slang::Extensions::ExtensionMethods& methods) = 0;

public:
	const std::string& getName() const {
		return mName;
	}

private:
	std::string mName;
};


namespace Slang {
namespace Extensions {


typedef std::list<AExtension*> ExtensionList;


}
}


#endif
