
#ifndef ObjectiveScript_RTTI_h
#define ObjectiveScript_RTTI_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class RTTI
{
public:
	RTTI()
	: mFilename("<unknown file>"),
	  mTypename("<unknown type>")
	{ }

	RTTI(const std::string& type, const std::string& filename)
	: mFilename(filename),
	  mTypename(type)
	{ }

public:
/*
	const std::string& name() const {
		return mName;
	}

	const std::string& type() const {
		return mTypename;
	}
*/

	const std::string& Filename() const {
		return mFilename;
	}

	const std::string& Typename() const {
		return mTypename;
	}

protected:
/*
	std::string mName;
*/

private:
	std::string mFilename;
	std::string mTypename;
};


}


#endif
