
#ifndef ObjectiveScript_Extensions_Mysql_MysqlExtension_h
#define ObjectiveScript_Extensions_Mysql_MysqlExtension_h


// Library includes

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


class MysqlExtension : public AExtension
{
public:
	MysqlExtension();

public:
	void provideMethods(ExtensionMethods &methods);
};


}
}
}



#endif
