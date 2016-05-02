
// Header
#include "MysqlExtension.h"

// Library includes

// Project includes
#include "AffectedRows.h"
#include "Close.h"
#include "Connect.h"
#include "ConnectionTest.h"
#include "Error.h"
#include "FieldCount.h"
#include "FreeResult.h"
#include "GetClientInfo.h"
#include "GetFieldName.h"
#include "GetFieldValue.h"
#include "Info.h"
#include "Init.h"
#include "NextResult.h"
#include "NextRow.h"
#include "NumFields.h"
#include "NumRows.h"
#include "Query.h"
#include "MysqlRealEscapeString.h"
#include "StoreResult.h"
#include "UseResult.h"

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
	methods.push_back(new MysqlFieldCount());
	methods.push_back(new MysqlFreeResult());
	methods.push_back(new MysqlGetFieldName());
	methods.push_back(new MysqlGetFieldValue());
	methods.push_back(new MysqlInfo());
	methods.push_back(new MysqlInit());
	methods.push_back(new MysqlNextResult());
	methods.push_back(new MysqlNextRow());
	methods.push_back(new MysqlNumFields());
	methods.push_back(new MysqlNumRows());
	methods.push_back(new MysqlQuery());
	methods.push_back(new MysqlRealEscapeString());
	methods.push_back(new MysqlRealConnect());
	methods.push_back(new MysqlStoreResult());
	methods.push_back(new MysqlUseResult());
}


}
}
}
