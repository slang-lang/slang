
#ifndef Core_Runtime_ControlFlow_h
#define Core_Runtime_ControlFlow_h


// Library includes

// Project includes

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
		Normal,
		Return,
		Throw
	} E;
};


}
}


#endif
