
// Header
#include "Threads.h"

// Library includes
#include <iostream>
#include <sstream>

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
	while ( !mStackFrames.empty() ) {
		popFrame();
	}
}

StackFrame* Thread::currentFrame() const
{
	if ( mStackFrames.empty() ) {
		return 0;
	}

	return mStackFrames.back();
}

void Thread::deinit()
{
	mState = State::Stopped;
}

Runtime::ControlFlow::E Thread::execute(Runtime::Object* self, Common::Method* method, const ParameterList& params, Runtime::Object* result)
{
	mState = State::Started;

	AST::TreeInterpreter interpreter(mId);
	Runtime::ControlFlow::E controlflow = interpreter.execute(self, method, params, result);

	mState = State::Stopping;

	// shutdown things...

	mState = State::Stopped;

	return controlflow;
}

Runtime::ExceptionData& Thread::exception()
{
	return mExceptionData;
}

void Thread::exception(Runtime::Object* data, const Common::Position& position)
{
	mExceptionData = Runtime::ExceptionData(data, position, stackTrace());
}

StackFrame* Thread::frame(Common::FrameId frameId) const
{
	size_t idx = 0;
	for ( StackFrames::const_iterator it = mStackFrames.cbegin(); it != mStackFrames.cend(); ++it, ++idx ) {
		if ( idx == frameId ) {
			return (*it);
		}
	}

	return 0;
}

Common::ThreadId Thread::getId() const
{
	return mId;
}

Common::FrameId Thread::getNumFrames() const
{
	return mStackFrames.size();
}

Thread::State::E Thread::getState() const
{
	return mState;
}

void Thread::init()
{
	mState = State::Started;
}

void Thread::popFrame()
{
	StackFrame* frame = mStackFrames.back();
	frame->popTokens();
	frame->popScope();

	mStackFrames.pop_back();

	delete frame;
}

void Thread::print()
{
	for ( StackFrames::const_iterator it = mStackFrames.begin(); it != mStackFrames.end(); ++it ) {
		std::cout << "Thread " << mId << ": " << (*it)->toString() << std::endl;
	}
}

void Thread::pushFrame(IScope* scope, const TokenList& tokens, const ParameterList& params)
{
	// create new stack frame
	StackFrame* frame = new StackFrame(mStackFrames.size(), scope, params);
	// push scope
	frame->pushScope(scope, false, false);
	// push tokens (although maybe none are present)
	frame->pushTokens(tokens);

	mStackFrames.push_back(frame);
}

std::string Thread::stackTrace() const
{
	std::stringstream ss;

	for ( StackFrames::const_iterator it = mStackFrames.begin(); it != mStackFrames.end(); ++it ) {
		ss << "Thread " << mId << ": " << (*it)->toString() << std::endl;
	}

	return ss.str();
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

void Threads::print()
{
	for ( InternalThreads::iterator it = mThreads.begin(); it != mThreads.end(); ++it ) {
		it->second->print();
	}
}


}
