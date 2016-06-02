
#ifndef Core_Runtime_ControlFlow_h
#define Core_Runtime_ControlFlow_h


// Library includes

// Project includes
#include <string>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class ControlFlow
{
public:
	typedef enum {
		Break,
		Continue,
		ExitProgram,
		Normal,
		Return,
		Throw
	} E;

	static std::string toString(E e) {
		switch ( e ) {
			case Break: return "Break";
			case Continue: return "Continue";
			case ExitProgram: return "ExitProgram";
			case Normal: return "Normal";
			case Return: return "Return";
			case Throw: return "Throw";
		}

		return "Undefined";
	}
};


}
}


#endif
