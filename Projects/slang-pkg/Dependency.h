
#ifndef Slang_slang_pkg_Dependency_h
#define Slang_slang_pkg_Dependency_h


// Library includes
#include <set>
#include <string>
#include <utility>

// Project includes

// Forward declarations

// Namespace declarations


class Dependency
{
public:
	Dependency( std::string module, std::string minVersion, std::string maxVersion, std::string source )
	: MaxVersion( std::move( maxVersion ) ),
	  MinVersion( std::move( minVersion ) ),
	  Module( std::move( module ) ),
	  Source( std::move( source ) )
	{ }

public:
	bool operator<( const Dependency& other ) const {
		return Module < other.Module;
	}

public:
	std::string MaxVersion;
	std::string MinVersion;
	std::string Module;
	std::string Source;
};

typedef std::set<Dependency> Dependencies;


#endif
