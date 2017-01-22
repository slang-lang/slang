
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
  mThreads(0),
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
	mThreads->deinit();
	mMemory->deinit();
	mRepository->deinit();
	//mVirtualMethodTable->deinit();

	delete mStack;
	delete mThreads;
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
	mThreads = new Threads();
	mVirtualMethodTable = new VirtualMethodTable();

	//mVirtualMethodTable->init();
	mMemory->init();
	mStack->init();
	mRepository->init();
	mThreads->init();

	mInitialized = true;
}

Memory* Controller::memory() const
{
	return mMemory;
}

Repository* Controller::repository() const
{
	return mRepository;
}

Stack* Controller::stack() const
{
	return mStack;
}

Thread* Controller::thread(Common::ThreadId id) const
{
	return mThreads->getThread(id);
}

Threads* Controller::threads() const
{
	return mThreads;
}

VirtualMethodTable* Controller::virtualMethodTable() const
{
	return mVirtualMethodTable;
}


}
