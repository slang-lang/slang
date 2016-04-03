
// Header
#include "MysqlExtension.h"

// Library includes
#include <cassert>

// Project includes
#include "Close.h"
#include "Connect.h"
#include "ConnectionTest.h"
#include "GetClientInfo.h"
#include "Info.h"
#include "Init.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


void MysqlExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	// Testing
	// {
	methods.push_back(new ConnectionTest());
	// }

	methods.push_back(new MysqlClose());
	methods.push_back(new MysqlGetClientInfo());
	methods.push_back(new MysqlRealConnect());
	methods.push_back(new MysqlInfo());
	methods.push_back(new MysqlInit());
}


}
}
}
