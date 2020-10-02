
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

namespace Extensions {

class AExtension
{
public:
	AExtension( std::string name, std::string version )
	: mName( std::move( name ) )
	, mVersion( std::move( version ) )
	{ }
	virtual ~AExtension() = default;

public:
	virtual void initialize( Slang::IScope* scope ) = 0;
	virtual void provideMethods( Slang::Extensions::ExtensionMethods& methods ) = 0;

public:
	const std::string& getName() const {
		return mName;
	}

	const std::string& getVersion() const {
		return mVersion;
	}

protected:
	std::string mName;
	std::string mVersion;
};

typedef std::list<AExtension*> ExtensionCollection;


}
}


#endif
