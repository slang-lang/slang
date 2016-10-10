
// Header
#include "Memory.h"

// Library includes
#ifdef _WIN32
#else
#	include <stdint.h>
#endif

// Project includes
#include <Core/Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


Memory::Memory()
: mNextAddress(1),
  mNull(0)
{
}

Memory::~Memory()
{
/*
	for ( MemoryMap::iterator it = mMemory.begin(); it != mMemory.end(); ++it ) {
		delete it->second;
		it->second = 0;
	}
	mMemory.clear();
*/

	MemoryMap tmp = mMemory;

	for ( MemoryMap::iterator it = tmp.begin(); it != tmp.end(); ++it ) {
		deleteObject(it->first);
	}
}

void Memory::deleteObject(const Reference& ref)
{
	MemoryMap::iterator it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid delete for address ");//+ std::string(ref.getAddress()));
	}

	// delete it if it's valid ...
	if ( it->second ) {
		it->second->Destructor();

		delete it->second;
		it->second = 0;
	}

	// ... and remove address from memory
	mMemory.erase(it);
}

const Reference& Memory::getAddress(Runtime::Object *obj) const
{
	for ( MemoryMap::const_iterator it = mMemory.begin(); it != mMemory.end(); ++it ) {
		if ( it->second == obj ) {
			return it->first;
		}
	}

	return mNull;
}

Memory& Memory::GetInstance()
{
	static Memory instance;

	return instance;
}

const Reference& Memory::getNullReference() const
{
	return mNull;
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

Runtime::Object* Memory::getObject(const Reference& ref) const
{
	for ( MemoryMap::const_iterator it = mMemory.begin(); it != mMemory.end(); ++it ) {
		if ( it->first == ref ) {
			return it->second;
		}
	}

	return 0;
}

const Reference& Memory::newObject(Runtime::Object *obj)
{
	const Reference& ref = reserveAddress();

	mMemory[ref] = obj;
	obj->setReference(ref);

	return ref;
}


}
