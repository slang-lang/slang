
// Header
#include "MysqlExtension.h"

// Library includes
#include <cassert>

// Project includes
#include "AffectedRows.h"
#include "Close.h"
#include "Connect.h"
#include "ConnectionTest.h"
#include "Error.h"
#include "FreeResult.h"
#include "GetClientInfo.h"
#include "Info.h"
#include "Init.h"
#include "NumRows.h"
#include "Query.h"
#include "StoreResult.h"

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

	methods.push_back(new MysqlAffectedRows());
	methods.push_back(new MysqlClose());
	methods.push_back(new MysqlGetClientInfo());
	methods.push_back(new MysqlError());
	methods.push_back(new MysqlFreeResult());
	methods.push_back(new MysqlInfo());
	methods.push_back(new MysqlInit());
	methods.push_back(new MysqlNumRows());
	methods.push_back(new MysqlQuery());
	methods.push_back(new MysqlRealConnect());
	methods.push_back(new MysqlStoreResult());
}


}
}
}
