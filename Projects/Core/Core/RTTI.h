
#ifndef ObjectiveScript_RTTI_h
#define ObjectiveScript_RTTI_h


// Library includes
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class OSRTTI
{
public:
	OSRTTI()
	{ }

	OSRTTI(const std::string& type)
	: mTypename(type)
	{ }

public:
	const std::string& Typename() const {
		return mTypename;
	}

protected:

private:
	std::string mTypename;
};


}


#endif
