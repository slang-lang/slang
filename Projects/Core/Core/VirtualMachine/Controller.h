
#ifndef Slang_Core_Core_VirtualMachine_Controller_h
#define Slang_Core_Core_VirtualMachine_Controller_h


// Library includes

// Project includes
#include "Memory.h"
#include "Repository.h"
#include "Threads.h"
#include "TypeSystem.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Common {
	class Namespace;
}

class Controller
{
public:
// Singleton
// {
public:
	static Controller& Instance();
// }

public:
	class Phase {
	public:
		enum E {
			Startup,
			Preparation,
			Generation,
			Optimization,
			Execution,
			Shutdown
		};
	};

public:
	~Controller() = default;

public:
	void deinit();
	void init();

	Phase::E phase() const;
	void phase(Phase::E value);

public:
	Common::Namespace* globalScope() const;
	Memory* memory() const;
	Repository* repository() const;
	Thread* thread(Common::ThreadId id) const;
	Threads* threads() const;
	TypeSystem* typeSystem() const;

private:
	Controller();
	Controller(Controller const&)/* = delete*/;
	void operator=(Controller const&)/* = delete*/;

private:
	Common::Namespace* mGlobalScope;
	Memory* mMemory;
	Phase::E mPhase;
	Repository* mRepository;
	Threads* mThreads;
	TypeSystem* mTypeSystem;
};


}


#endif
