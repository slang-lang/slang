
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
: mNextAddress(1),
  mNull(0)
{
}

Memory::~Memory()
{
}

void Memory::add(const Reference &ref)
{
	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	it->second.mCount += 1;
}

void Memory::deinit()
{
/*
	MemoryMap tmp = mMemory;

	for ( MemoryMap::iterator it = tmp.begin(); it != tmp.end(); ++it ) {
		deleteObject(it->first);
	}
*/
}

void Memory::deleteObject(const Reference& ref)
{
	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid delete for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	// delete it if it's valid ...
	if ( it->second.mObject ) {
		it->second.mObject->Destructor();

		it->second.mObject->setReference(0);

		delete it->second.mObject;
		it->second.mObject = 0;
	}

	// reset reference counter
	it->second.mCount = 0;

	// ... and remove address from memory
	//mMemory.erase(it);
}

Runtime::Object* Memory::get(const Reference &ref) const
{
	MemoryMap::const_iterator it = mMemory.find(ref);
	if ( it != mMemory.end() ) {
		return it->second.mObject;
	}

	return 0;
}

const Reference& Memory::getNullReference() const
{
	return mNull;
}

void Memory::init()
{

}

const Reference& Memory::newObject(Runtime::Object *obj)
{
	const Reference& ref = reserveAddress();

	mMemory[ref].mCount = 0;
	mMemory[ref].mObject = obj;

	obj->setReference(ref);

	return ref;
}

void Memory::remove(const Reference &ref)
{
	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Tools::ConvertToStdString(ref.getAddress()));
	}

	it->second.mCount -= 1;
	if ( it->second.mCount == 0 ) {
		deleteObject(it->first);
	}
}

const Reference& Memory::reserveAddress()
{
	// 1) the simple way:
	//    only use an address once, so that no address can get
	//    reused and we accidentally make a forgotten reference
	//    valid again although its object has been deleted
	//    long ago;
	if ( mNextAddress >= SIZE_MAX - 1 ) {
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
	Reference ref(mNextAddress++);
	mMemory[ref] = 0;

	return mMemory.rbegin()->first;
}


}
