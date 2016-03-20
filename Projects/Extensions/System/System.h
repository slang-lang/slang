
#ifndef ObjectiveScript_Extensions_System_System_h
#define ObjectiveScript_Extensions_System_System_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>
#include <Core/Method.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {


class Print : public Runtime::Method
{
public:
	Print();

public:
	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};

class PrintLine : public Runtime::Method
{
public:
	PrintLine();

public:
	Runtime::ControlFlow::E execute(const ParameterList &params, Runtime::Object *result);
};


class System : public IExtension
{
public:
	char *getName() const {
		return "System";
	}

	void provideMethods(ExtensionMethods &methods) {
		methods.push_back(new Print());
		methods.push_back(new PrintLine());
	}
};


}
}

#endif
