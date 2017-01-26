
// Header
#include <Core/Runtime/Exceptions.h>
#include "Threads.h"

// Library includes

// Project includes
#include "Stack.h"

// Namespace declarations


namespace ObjectiveScript {


Thread::Thread()
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
	if ( mState == State::Starting ) {
		mState = State::Started;
	}

	//pushFrame();
	// add parameters as locales
	Runtime::ControlFlow::E controlflow = mInterpreter.execute(method, params, result);
	//popFrame();

	if ( mState == State::Stopping ) {
		mState = State::Stopped;
	}

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

Common::ThreadId Threads::createThread()
{
	Thread* t = new Thread(mThreads.size());

	mThreads.insert(std::make_pair(t->getId(), t));

	return t->getId();
}

void Threads::deinit()
{
	// TODO: stop all currently running threads

	for ( InternalThreads::iterator it = mThreads.begin(); it != mThreads.end(); ++it ) {
		delete it->second;
		it->second = 0;
	}
	mThreads.clear();
}

void Threads::deleteThread(Common::ThreadId id)
{
	(void)id;
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
	// create main thread for program execution
	createThread();
}


}
