
#ifndef ObjectiveScript_Core_Interfaces_IRuntimeType_h
#define ObjectiveScript_Core_Interfaces_IRuntimeType_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class IRuntimeType
{
public:
	virtual ~IRuntimeType() { }

	virtual void initialize() = 0;
};


}


#endif
