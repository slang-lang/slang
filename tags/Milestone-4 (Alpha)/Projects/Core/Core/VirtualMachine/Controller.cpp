
// Header
#include "Controller.h"

// Library includes

// Project includes
#include <Core/Common/Namespace.h>

// Namespace declarations


namespace ObjectiveScript {


Controller::Controller()
: mGlobalScope(0),
  mMemory(0),
  mPhase(Phase::Startup),
  mRepository(0),
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
	assert(mPhase > Phase::Startup);

	delete mGlobalScope;
	mGlobalScope = 0;

	mThreads->deinit();
	mMemory->deinit();
	mRepository->deinit();
	mTypeSystem->deinit();

	delete mThreads;
	mThreads = 0;
	delete mMemory;
	mMemory = 0;
	delete mRepository;
	mRepository = 0;
	delete mTypeSystem;
	mTypeSystem = 0;

	mPhase = Phase::Shutdown;
}

Common::Namespace* Controller::globalScope() const
{
	return mGlobalScope;
}

void Controller::init()
{
	assert(mPhase == Phase::Startup || mPhase == Phase::Shutdown);

	assert(!mGlobalScope);
	mGlobalScope = new Common::Namespace(VALUE_NONE, 0);

	mMemory = new Memory();
	mRepository = new Repository();
	mThreads = new Threads();
	mTypeSystem = new TypeSystem();

	mTypeSystem->init();
	mMemory->init();
	mRepository->init();
	mThreads->init();

	mPhase = Phase::Preparation;
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
	mPhase = value;
}

Repository* Controller::repository() const
{
	return mRepository;
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