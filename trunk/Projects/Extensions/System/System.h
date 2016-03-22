
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>
#include "AssertMsg.h"
#include "Print.h"
#include "Write.h"
#include "WriteLn.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class System : public IExtension
{
public:
	std::string getName() const {
		return "System";
	}

	void provideMethods(ExtensionMethods &methods) {
		assert(methods.empty());

		methods.push_back(new AssertMsg());
		methods.push_back(new Printf());
		methods.push_back(new Write());
		methods.push_back(new WriteLn());
	}
};


}
}

#endif
