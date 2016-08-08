
#ifndef ObjectiveScript_Extensions_Mysql_MysqlExtension_h
#define ObjectiveScript_Extensions_Mysql_MysqlExtension_h


// Library includes

// Project includes
#include <Core/Interfaces/IExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlExtension : public IExtension
{
public:
	std::string getName() const {
		return "Mysql";
	}

	void provideMethods(ExtensionMethods &methods);
};


}
}
}



#endif
