
// Header
#include "Threads.h"

// Library includes

// Project includes
#ifdef USE_AST_PARSE_TREE
#	include <Core/AST/TreeInterpreter.h>
#else
#	include <Core/Runtime/Interpreter.h>
#endif
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

#ifdef USE_AST_PARSE_TREE

	AST::TreeInterpreter ti(mId);
	Runtime::ControlFlow::E controlflow = ti.execute(method, params, result);

#else

	Runtime::Interpreter interpreter(mId);
	Runtime::ControlFlow::E controlflow = interpreter.execute(method, params, result);

#endif

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