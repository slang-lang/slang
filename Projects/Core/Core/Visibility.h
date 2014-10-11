
#ifndef ObjectiveScript_Visibility_h
#define ObjectiveScript_Visibility_h


// Library includes
#include <cassert>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Visibility
{
public:
	enum E {
		Private = 0,
		Protected,
		Public
	};

	static E convert(const std::string& v) {
		if ( v == "private" ) { return Private; }
		else if ( v == "protected" ) { return Protected; }
		else if ( v == "public" ) { return Public; }

		assert(!"invalid visibility!");
		return Private;
	}
};


}


#endif
