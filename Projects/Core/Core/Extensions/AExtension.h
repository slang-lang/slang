#ifndef Slang_Core_Core_Extensions_AExtension_h
#define Slang_Core_Core_Extensions_AExtension_h


// Library includes
#include <list>
#include <string>
#include <utility>

// Project includes
#include "ExtensionMethod.h"
#include "ExtensionNamespace.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class IScope;

namespace Extensions {

class AExtension
{
public:
	explicit AExtension( const std::string& name, const std::string& version = "" )
	: mName( name )
	, mVersion( version )
	{ }
	virtual ~AExtension() = default;

public:
	virtual void initialize( ExtensionNamespace* space ) = 0;
	virtual void provideMethods( ExtensionMethods& methods ) = 0;

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
