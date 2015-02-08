
#ifndef ObjectiveScript_Memory_h
#define ObjectiveScript_Memory_h


// Library includes
#include <map>

// Project includes
#include "Object.h"
#include "Reference.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Memory
{
public:
	Memory();
	~Memory();

public:
	void deleteObject(const Reference& ref);
	const Reference& newObject(Object *obj);

public:
	const Reference& getAddress(Object *obj) const;
	const Reference& getNullReference() const;
	Object* getObject(const Reference& ref) const;
	Object* getObject(const std::string& name) const;

protected:

private:
	typedef std::map<Reference, Object*> MemoryMap;

private:
	const Reference& reserveAddress();

private:
	MemoryMap mMemory;
	size_t mNextAddress;
	Reference mNull;
};


}


#endif
