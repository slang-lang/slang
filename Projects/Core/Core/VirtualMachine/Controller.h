
#ifndef Slang_Core_Core_VirtualMachine_Controller_h
#define Slang_Core_Core_VirtualMachine_Controller_h


// Library includes

// Project includes
#include <Core/Defines.h>
#include "Memory.h"
#include "Repository.h"
#include "Threads.h"

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
namespace Common {
	class Namespace;
}

class SLANG_API Controller
{
public:
	static Controller& Instance() {
		static Controller instance;
		return instance;
	}

public:
	class Phase
	{
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

	Controller(const Controller&) = delete;
	Controller& operator=(const Controller&) = delete;

public:
	void deinit();
	void init();

	Phase::E phase() const;
	void phase(Phase::E value);

public:
	Common::Namespace* globalScope() const;
	Memory* memory() const;
	Repository* repository() const;
	Thread* thread(ThreadId id) const;
	Threads* threads() const;

private:
	Controller();

private:
	Common::Namespace* mGlobalScope;
	Memory* mMemory;
	Phase::E mPhase;
	Repository* mRepository;
	Threads* mThreads;
};


}


#endif
