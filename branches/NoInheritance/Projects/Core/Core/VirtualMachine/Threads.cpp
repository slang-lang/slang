
// Header
#include "Threads.h"

// Library includes

// Project includes
#include <Core/AST/TreeInterpreter.h>
#include <Core/Common/Method.h>
#include <Core/Runtime/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


Thread::Thread()
: mId(0),
  mState(State::Starting)
{
}

Thread::Thread(Common::ThreadId id)
: mId(id),
  mState(State::Starting)
{
}

Thread::~Thread()
{
}

void Thread::deinit()
{
	mState = State::Stopped;
}

Runtime::ControlFlow::E Thread::execute(Common::Method* method, const ParameterList& params, Runtime::Object* result)
{
	mState = State::Started;

	AST::TreeInterpreter interpreter(mId);
	Runtime::ControlFlow::E controlflow = interpreter.execute(method, params, result);

	mState = State::Stopping;

	return controlflow;
}

Common::ThreadId Thread::getId() const
{
	return mId;
}

Thread::State::E Thread::getState() const
{
	return mState;
}

void Thread::init()
{
	mState = State::Started;
}


Threads::Threads()
{
}

Threads::~Threads()
{
}

Thread* Threads::createThread()
{
	Thread* t = new Thread(mThreads.size());
	// initialize thread
	t->init();

	mThreads.insert(std::make_pair(t->getId(), t));

	return t;
}

void Threads::deinit()
{
	// TODO: stop all currently running threads

	for ( InternalThreads::iterator it = mThreads.begin(); it != mThreads.end(); ++it ) {
		// deinitialize thread
		it->second->deinit();

		delete it->second;
		it->second = 0;
	}
	mThreads.clear();
}

void Threads::deleteThread(Common::ThreadId id)
{
	Thread* thread = getThread(id);

	(void)thread;
}

unsigned int Threads::getNumThreads() const
{
	return mThreads.size();
}

Thread* Threads::getThread(Common::ThreadId id) const
{
	InternalThreads::const_iterator it = mThreads.find(id);
	if ( it == mThreads.end() ) {
		// queried thread does not exist!
		throw Runtime::Exceptions::RuntimeException("invalid thread id");
	}

	return it->second;
}

void Threads::init()
{
	// nothing to do here atm
}


}
