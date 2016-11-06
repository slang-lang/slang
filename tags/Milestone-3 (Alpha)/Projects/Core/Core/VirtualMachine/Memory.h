
#ifndef ObjectiveScript_Core_VirtualMachine_Memory_h
#define ObjectiveScript_Core_VirtualMachine_Memory_h


// Library includes
#include <map>

// Project includes
#include <Core/Object.h>
#include <Core/Reference.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Memory
{
public:
	Memory();
	~Memory();

public:
	void deinit();
	void init();

public:
	const Reference& getNullReference() const;
	Runtime::Object* get(const Reference &ref) const;
	const Reference& newObject(Runtime::Object *obj);

	void add(const Reference &ref);
	void remove(const Reference &ref);

private:
	class RefCount
	{
	public:
		RefCount(Runtime::Object* object = 0)
		: mCount(0),
		  mObject(object)
		{ }

	public:
		unsigned int mCount;
		Runtime::Object* mObject;
	};
	typedef std::map<Reference, RefCount> MemoryMap;

private:
	Memory(Memory const&)/* = delete*/;
	void operator=(Memory const&)/* = delete*/;

private:
	void deleteObject(const Reference& ref);
	const Reference& reserveAddress();

private:
	MemoryMap mMemory;
	size_t mNextAddress;
	Reference mNull;
};


}


#endif
