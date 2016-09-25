
#ifndef ObjectiveScript_Core_Reference_h
#define ObjectiveScript_Core_Reference_h


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
	Reference(unsigned int address);

public:
	unsigned int getAddress() const;
	bool isValid() const;

public:
	bool operator< (const Reference& other) const;
	bool operator== (const Reference& other) const;

protected:

private:
	unsigned int mAddress;
};


typedef std::list<Reference> ReferencesList;


}


#endif
