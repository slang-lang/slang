
// Header
#include "Memory.h"

// Library includes
#ifdef _WIN32
#else
#	include <stdint.h>
#endif

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Tools.h>

// Namespace declarations


namespace ObjectiveScript {


Memory::Memory()
: mNextAddress(1)
{
}

Memory::~Memory()
{
}

void Memory::add(const Runtime::Reference &ref)
{
	if ( !ref.isValid() ) {
		// cannot add address 0
		return;
	}

	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	it->second.mCount++;
}

void Memory::deinit()
{
}

void Memory::deleteObject(const Runtime::Reference& ref)
{
	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid delete for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	Runtime::Object* object = it->second.mObject;

	// reset reference counter
	it->second.mCount = 0;
	it->second.mObject = 0;

	// ... and remove address from memory
	mMemory.erase(it);

	// delete it if it's valid ...
	if ( object ) {
		object->Destructor();

		object->setReference(Runtime::NullReference);

		delete object;
	}
}

Runtime::Object* Memory::get(const Runtime::Reference &ref) const
{
	MemoryMap::const_iterator it = mMemory.find(ref);
	if ( it != mMemory.end() ) {
		return it->second.mObject;
	}

	return 0;
}

void Memory::init()
{
}

const Runtime::Reference& Memory::newObject(Runtime::Object *obj)
{
	const Runtime::Reference& ref = reserveAddress();

	mMemory[ref].mCount = 0;
	mMemory[ref].mObject = obj;

	obj->setReference(ref);

	return ref;
}

void Memory::remove(const Runtime::Reference &ref)
{
	if ( !ref.isValid() ) {
		// cannot delete address 0
		return;
	}

	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	it->second.mCount--;
	if ( it->second.mCount == 0 ) {
		deleteObject(it->first);
	}
}

const Runtime::Reference& Memory::reserveAddress()
{
	// 1) the simple way:
	//    only use an address once, so that no address can get
	//    reused and we accidentally make a forgotten reference
	//    valid again although its object has been deleted
	//    long ago;
	if ( mNextAddress >= (unsigned int)-1 ) {
		// 2) the more sophisticated way:
		//    as soon as we run out of fresh addresses reuse
		//    one that's not actually referencing a valid object
		//    (that means any reference that is NOT in our memory,
		//    a good guess would be to pick the oldest [=lowest]
		//    address again);
		//TODO: implement me

		throw Common::Exceptions::Exception("memory exhausted!");
	}

	// reserve address by creating a new reference
	// and inserting it into our memory
	Runtime::Reference ref(mNextAddress++);
	mMemory[ref] = RefCount();

	return mMemory.rbegin()->first;
}


}
