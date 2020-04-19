
#ifndef Slang_Core_Core_Runtime_Reference_h
#define Slang_Core_Core_Runtime_Reference_h


// Library includes
#include <list>

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class Reference
{
public:
	Reference();
	explicit Reference(MemoryId address);

public:
	MemoryId getAddress() const;
	bool isValid() const;

public:
	bool operator< (const Reference& other) const;
	bool operator== (const Reference& other) const;

private:
	MemoryId mAddress;
};


typedef std::list<Reference> ReferencesList;


static const Reference NullReference = Reference();


}
}


#endif
