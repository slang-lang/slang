
#ifndef Slang_slang_pkg_Repository_h
#define Slang_slang_pkg_Repository_h


// Library includes
#include <string>

// Project includes
#include "Module.h"

// Forward declarations

// Namespace declarations


class Repository
{
public:

	class Authentication
	{
	public:
		enum E {
			None,
			Basic,
			Bearer
		};
	};

public:
	explicit Repository( std::string name = "" );
	~Repository() = default;

public:
	void addModule( const Module& module );
	bool contains( const Module& module ) const;
	bool getModule( const std::string& shortName, Module& module ) const;

	bool processIndex( const Json::Value& value );

public:

	Authentication::E getAuthentication() const {
		return mAuthentication;
	}
	void setAuthentication( Authentication::E authentication ) {
		mAuthentication = authentication;
	}

	const std::string& getAuthorization() const {
		return mAuthorization;
	}
	void setAuthorization( const std::string& authorization ) {
		mAuthorization = authorization;
	}

	const Modules& getModules() const {
		return mModules;
	}

	const std::string& getName() const {
		return mName;
	}

	const std::string& getURL() const {
		return mURL;
	}
	void setURL( const std::string& url ) {
		mURL = url;
	}

private:
	Authentication::E mAuthentication;
	std::string mAuthorization;
	Modules mModules;
	std::string mName;
	std::string mURL;
};


#endif
