
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
	const Reference& newObject(Runtime::Object *obj);

public:
	const Reference& getAddress(Runtime::Object *obj) const;
	const Reference& getNullReference() const;
	Runtime::Object* getObject(const Reference& ref) const;

protected:

private:
	typedef std::map<Reference, Runtime::Object*> MemoryMap;

private:
	const Reference& reserveAddress();

private:
	MemoryMap mMemory;
	size_t mNextAddress;
	Reference mNull;
};


}


#endif
