
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
	explicit Reference(size_t address);

public:
	size_t getAddress() const;
	bool isValid() const;

public:
	bool operator< (const Reference& other) const;
	bool operator== (const Reference& other) const;

private:
	size_t mAddress;
};


typedef std::list<Reference> ReferencesList;


static const Reference NullReference = Reference(0);


}


#endif
