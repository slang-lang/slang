
#ifndef ObjectiveScript_Core_VirtualMachine_Threads_h
#define ObjectiveScript_Core_VirtualMachine_Threads_h


// Library includes
#include <map>

// Project includes
#include <Core/Interpreter.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
}
namespace Runtime {
	class Object;
}
class Threads;


typedef unsigned int ThreadId;


class Thread : public Stack
{
public:
	class State
	{
	public:
		enum E {
			Starting,
			Started,
			Pausing,
			Paused,
			Stopping,
			Stopped
		};
	};

public:
	Thread();
	Thread(ThreadId id, Threads* threadController);
	~Thread();

public:
	void deinit();
	Runtime::ControlFlow::E execute(Common::Method* method, const ParameterList& params, Runtime::Object* result);
	void init();

public:
	ThreadId getId() const;
	State::E getState() const;

private:
	ThreadId mId;
	Runtime::Interpreter mInterpreter;
	State::E mState;
	Threads* mThreadController;
};


class Threads
{
public:
	Threads();
	~Threads();

public:
	void deinit();
	void init();

public:
	ThreadId createThread();
	void deleteThread(ThreadId id);
	Thread* getThread(ThreadId id) const;

	unsigned int getNumThreads() const;

private:
	typedef std::map<unsigned int /*id*/, Thread*> InternalThreads;

private:
	InternalThreads mThreads;
};


}


#endif
