
#ifndef ObjectiveScript_Core_VirtualMachine_Controller_h
#define ObjectiveScript_Core_VirtualMachine_Controller_h


// Library includes

// Project includes
#include "Memory.h"
#include "Repository.h"
#include "Stack.h"
#include "Threads.h"
#include "TypeSystem.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Controller
{
public:
// Singleton
// {
public:
	static Controller& Instance();
// }

public:
	~Controller();

public:
	void deinit();
	void init();
	bool isInitialized() const;

public:
	Memory* memory() const;
	Repository* repository() const;
	Stack* stack() const;
	Thread* thread(Common::ThreadId id) const;
	Threads* threads() const;
	TypeSystem* typeSystem() const;

private:
	Controller();
	Controller(Controller const&)/* = delete*/;
	void operator=(Controller const&)/* = delete*/;

private:
	bool mInitialized;
	Memory* mMemory;
	Repository* mRepository;
	Stack* mStack;
	Threads* mThreads;
	TypeSystem* mTypeSystem;
};


}


#endif
