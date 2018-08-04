
#ifndef ObjectiveScript_Core_VirtualMachine_Threads_h
#define ObjectiveScript_Core_VirtualMachine_Threads_h


// Library includes
#include <list>
#include <map>

// Project includes
#include <Core/Common/Types.h>
#include <Core/Designtime/Parser/Token.h>
#include <Core/Parameter.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/VirtualMachine/StackFrame.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
}
class IScope;
namespace Runtime {
	class Object;
}


class Thread
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

public:	// Initialization
	void deinit();
	Runtime::ControlFlow::E execute(Runtime::Object* self, Common::Method* method, const ParameterList& params, Runtime::Object* result);
	void init();
	void print();

public:	// Thread specificas
	Common::ThreadId getId() const;
	State::E getState() const;

public:	// StackFrame specificas
	StackFrame* currentFrame() const;
	StackFrame* frame(Common::FrameId frameId) const;
	Common::FrameId getNumFrames() const;

	Runtime::ExceptionData& exception();

	void popFrame();
	void pushFrame(IScope* scope, const TokenList& tokens, const ParameterList& params);

private:
	typedef std::list<StackFrame*> StackFrames;

private:
	Runtime::ExceptionData mExceptionData;
	Common::ThreadId mId;
	StackFrames mStackFrames;
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
