
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
  mTypeSystem(0)
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
	mTypeSystem->deinit();

	delete mStack;
	delete mThreads;
	delete mMemory;
	delete mRepository;
	delete mTypeSystem;

	mInitialized = false;
}

void Controller::init()
{
	assert(!mInitialized);

	mMemory = new Memory();
	mRepository = new Repository();
	mStack = new Stack();
	mThreads = new Threads();
	mTypeSystem = new TypeSystem();

	mTypeSystem->init();
	mMemory->init();
	mStack->init();
	mRepository->init();
	mThreads->init();

	mInitialized = true;
}

bool Controller::isInitialized() const
{
	return mInitialized;
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

TypeSystem* Controller::typeSystem() const
{
	return mTypeSystem;
}


}
