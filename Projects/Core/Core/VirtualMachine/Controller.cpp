
// Header
#include "Controller.h"

// Library includes

// Project includes

// Namespace declarations


namespace ObjectiveScript {


Controller::Controller()
: mMemory(0),
  mPhase(Phase::Preparation),
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
	assert(mPhase > Phase::Preparation);

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

	mPhase = Phase::Shutdown;
}

void Controller::init()
{
	assert(mPhase == Phase::Preparation || mPhase == Phase::Shutdown);

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

	mPhase = Phase::Generation;
}

Memory* Controller::memory() const
{
	return mMemory;
}

Controller::Phase::E Controller::phase() const
{
	return mPhase;
}

void Controller::phase(Controller::Phase::E value)
{
	//assert(mPhase < value);

	mPhase = value;
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
