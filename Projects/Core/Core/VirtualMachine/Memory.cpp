
// Header
#include "Memory.h"

// Library includes
#ifdef _WIN32
#else
#	include <cstdint>
#endif

// Project includes
#include <Core/Common/Exceptions.h>
#include <Core/Object.h>
#include <Logger/Logger.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace Slang {


Memory::Memory()
: mNextAddress(1)
{
}

Memory::~Memory()
{
	deinit();
}

void Memory::add(const Runtime::Reference& ref)
{
	if ( !ref.isValid() ) {
		// cannot add address 0
		return;
	}

	auto it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Utils::Tools::toString(ref.getAddress()));
	}

	it->second.mCount++;
}

void Memory::deinit()
{
	for ( auto& it : mMemory ) {
		/*
		if( it.second.mObject ) {
			std::cout << "Address " << it.first.getAddress() << " is referenced " << it.second.mCount << " time(s)." << std::endl;
		}
		*/

		//it.second.mObject->Destructor();

		// force delete
		delete it.second.mObject;
	}

	mMemory.clear();
}

void Memory::deleteObject(const Runtime::Reference& ref)
{
	auto it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid delete for address " + Utils::Tools::toString(ref.getAddress()));
	}

	// delete it if it's valid ...
	if ( it->second.mObject ) {
		it->second.mObject->Destructor();

		delete it->second.mObject;
	}

	// ... and remove the address from memory
	mMemory.erase(it);
}

Runtime::Object* Memory::get(const Runtime::Reference& ref) const
{
	auto it = mMemory.find(ref);
	if ( it != mMemory.end() ) {
		return it->second.mObject;
	}

	return nullptr;
}

void Memory::init()
{
}

const Runtime::Reference& Memory::newObject(Runtime::Object* obj)
{
	const Runtime::Reference& ref = reserveAddress();

	mMemory[ref].mCount = 0;
	mMemory[ref].mObject = obj;

	obj->setReference(ref);

	return ref;
}

void Memory::remove(const Runtime::Reference& ref)
{
	if ( !ref.isValid() ) {
		// cannot delete address 0
		return;
	}

	auto it = mMemory.find(ref);
	if ( it == mMemory.end() ) {
		throw Common::Exceptions::Exception("invalid access for address " + Utils::Tools::toString(ref.getAddress()));
	}

	it->second.mCount--;
	if ( it->second.mCount == 0 && it->second.mObject ) {
		deleteObject( it->first );
	}
}

const Runtime::Reference& Memory::reserveAddress()
{
	// 1) the simple way:
	//    only use an address once, so that no address can get
	//    reused and we accidentally make a forgotten reference
	//    valid again although its object has been deleted
	//    long ago;
	if ( mNextAddress >= static_cast<unsigned int>( -1 ) ) {
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