
// Header
#include "Controller.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Controller::Controller()
: mInitialized(false),
  mMemory(0),
  mRepository(0),
  mStack(0),
  mVirtualMethodTable(0)
{
}

Controller::~Controller()
{
}

Controller& Controller::Instance()
{
	static Controller instance;

	return instance;
}

void Controller::deinit()
{
	assert(mInitialized);

	mStack->deinit();
	mMemory->deinit();
	mRepository->deinit();
	//mVirtualMethodTable->deinit();

	delete mStack;
	delete mMemory;
	delete mRepository;
	delete mVirtualMethodTable;

	mInitialized = false;
}

void Controller::init()
{
	assert(!mInitialized);

	mMemory = new Memory();
	mRepository = new Repository();
	mStack = new Stack();
	mVirtualMethodTable = new VirtualMethodTable();

	//mVirtualMethodTable->init();
	mMemory->init();
	mStack->init();
	mRepository->init();

	mInitialized = true;
}

Memory* Controller::memory() const
{
	assert(mMemory);

	return mMemory;
}

Repository* Controller::repository() const
{
	assert(mRepository);

	return mRepository;
}

Stack* Controller::stack() const
{
	assert(mStack);

	return mStack;
}

VirtualMethodTable* Controller::virtualMethodTable() const
{
	assert(mVirtualMethodTable);

	return mVirtualMethodTable;
}


}
