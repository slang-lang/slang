
#ifndef ObjectiveScript_Core_VirtualMachine_Threads_h
#define ObjectiveScript_Core_VirtualMachine_Threads_h


// Library includes
#include <map>

// Project includes
#include <Core/Common/Types.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/VirtualMachine/Stack.h>

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
	Thread(Common::ThreadId id);
	~Thread();

public:
	void deinit();
	Runtime::ControlFlow::E execute(Common::Method* method, const ParameterList& params, Runtime::Object* result);
	void init();
	void print();

public:
	Common::ThreadId getId() const;
	State::E getState() const;

private:
	Common::ThreadId mId;
	State::E mState;
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
	Thread* createThread();
	void deleteThread(Common::ThreadId id);
	Thread* getThread(Common::ThreadId id) const;

	unsigned int getNumThreads() const;

	void print();

private:
	typedef std::map<unsigned int /*id*/, Thread* /*thread*/> InternalThreads;

private:
	InternalThreads mThreads;
};


}


#endif
