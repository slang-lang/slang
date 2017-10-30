
#ifndef ObjectiveScript_Core_VirtualMachine_Memory_h
#define ObjectiveScript_Core_VirtualMachine_Memory_h


// Library includes
#include <map>

// Project includes
#include <Core/Object.h>
#include <Core/Runtime/Reference.h>
#include <Core/Runtime/Types.h>

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
	Runtime::Object* get(const Runtime::Reference &ref) const;
	const Runtime::Reference& newObject(Runtime::Object *obj);

	void add(const Runtime::Reference &ref);
	void remove(const Runtime::Reference &ref);

private:
	class RefCount
	{
	public:
		explicit RefCount(Runtime::Object* object = 0)
		: mCount(0),
		  mObject(object)
		{ }

	public:
		unsigned int mCount;
		Runtime::Object* mObject;
	};

	typedef std::map<Runtime::Reference, RefCount> MemoryMap;

private:
	Memory(Memory const&)/* = delete*/;
	void operator=(Memory const&)/* = delete*/;

private:
	void deleteObject(const Runtime::Reference& ref);
	const Runtime::Reference& reserveAddress();

private:
	MemoryMap mMemory;
	Runtime::MemoryId mNextAddress;
};


}


#endif
