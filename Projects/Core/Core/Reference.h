
#ifndef ObjectiveScript_Reference_h
#define ObjectiveScript_Reference_h


// Library includes
#include <list>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Reference
{
public:
	Reference();
	Reference(size_t address);

public:
	size_t getAddress() const;
	bool isValid() const;

public:
	bool operator< (const Reference& other) const;
	bool operator== (const Reference& other) const;

protected:

private:
	size_t mAddress;
};


typedef std::list<Reference> ReferenceList;


}


#endif
