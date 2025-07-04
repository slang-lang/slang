
#ifndef Slang_Core_Core_VirtualMachine_Threads_h
#define Slang_Core_Core_VirtualMachine_Threads_h


// Library includes
#include <list>
#include <map>

// Project includes
#include <Core/Common/Token.h>
#include <Core/Common/Types.h>
#include <Core/Runtime/ControlFlow.h>
#include <Core/Runtime/ExceptionData.h>
#include <Core/Runtime/Parameter.h>
#include <Core/VirtualMachine/StackFrame.h>

// Forward declarations

// Namespace declarations


namespace Slang {

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
	explicit Thread(ThreadId id);
	~Thread();

public:	// Initialization
	void deinit();
	Runtime::ControlFlow::E execute(Runtime::Object* self, Common::Method* method, const ParameterList& params, Runtime::Object* result);
	void init();
	void print();

public:	// Thread specificas
	ThreadId getId() const;
	State::E getState() const;

public:	// StackFrame specificas
	StackFrame* currentFrame() const;
	StackFrame* frame(FrameId frameId) const;
	FrameId getNumFrames() const;
	std::string stackTrace() const;

	Runtime::ExceptionData& exception();
	void exception(Runtime::ExceptionData data);
	void exception(Runtime::Object* data, const Common::Position& position = Common::Position());

	void popFrame();
	void pushFrame(IScope* scope, const TokenList& tokens, const ParameterList& params);

private:
	typedef std::list<StackFrame*> StackFrames;

private:
	Runtime::ExceptionData mExceptionData;
	ThreadId mId;
	StackFrames mStackFrames;
	State::E mState;
};


class Threads
{
public:
	Threads() = default;
	~Threads() = default;

public:
	void deinit();
	void init();

public:
	Thread* createThread();
	void deleteThread(ThreadId id);
	Thread* getThread(ThreadId id) const;

	unsigned int getNumThreads() const;

	void print();

private:
	typedef std::map<unsigned int /*id*/, Thread* /*thread*/> InternalThreads;

private:
	InternalThreads mThreads;
};


}


#endif
