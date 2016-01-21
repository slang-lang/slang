
#ifndef ObjectiveScript_RTTI_h
#define ObjectiveScript_RTTI_h


// Library includes
#include <string>

// Project includes
#include <Core/Consts.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class RTTI
{
public:
	RTTI()
	: mFilename(SYSTEM_LIBRARY),
	  mTypename(ANONYMOUS_OBJECT)
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
	std::string mFilename;
	std::string mTypename;

private:

};


}


#endif
