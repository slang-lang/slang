
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

	virtual ~RTTI() { }

public:
	const std::string& Filename() const {
		return mFilename;
	}

	const std::string& Typename() const {
		return mTypename;
	}

protected:

private:
	std::string mFilename;
	std::string mTypename;
};


}


#endif
