
// Header
#include "Controller.h"

// Library includes

// Project includes
#include <Core/Common/Namespace.h>

// Namespace declarations


namespace Slang {


Controller::Controller()
: mGlobalScope(nullptr),
  mMemory(nullptr),
  mPhase(Phase::Startup),
  mRepository(nullptr),
  mThreads(nullptr),
  mTypeSystem(nullptr)
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
	mGlobalScope = nullptr;

	mMemory->deinit();
	mThreads->deinit();
	mRepository->deinit();
	mTypeSystem->deinit();

	delete mThreads;
	mThreads = nullptr;
	delete mMemory;
	mMemory = nullptr;
	delete mRepository;
	mRepository = nullptr;
	delete mTypeSystem;
	mTypeSystem = nullptr;

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
	mGlobalScope = new Common::Namespace(VALUE_NONE, nullptr);

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
