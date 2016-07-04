
// Header
#include "MysqlExtension.h"

// Library includes

// Project includes
#include "AffectedRows.h"
#include "Connect.h"
#include "Error.h"
#include "FreeResult.h"
#include "GetClientInfo.h"
#include "GetFieldName.h"
#include "GetFieldValue.h"
#include "MysqlClose.h"
#include "MysqlDataSeek.h"
#include "MysqlFieldCount.h"
#include "MysqlFieldSeek.h"
#include "MysqlFieldTell.h"
#include "MysqlInfo.h"
#include "MysqlInit.h"
#include "MysqlNumFields.h"
#include "MysqlPing.h"
#include "MysqlQuery.h"
#include "MysqlRealEscapeString.h"
#include "MysqlSelectDB.h"
#include "MysqlStat.h"
#include "MysqlStoreResult.h"
#include "MysqlUseResult.h"
#include "NextResult.h"
#include "NextRow.h"
#include "NumRows.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


void MysqlExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new MysqlAffectedRows());
	methods.push_back(new MysqlClose());
	methods.push_back(new MysqlDataSeek());
	methods.push_back(new MysqlError());
	methods.push_back(new MysqlFieldCount());
	methods.push_back(new MysqlFieldSeek());
	methods.push_back(new MysqlFieldTell());
	methods.push_back(new MysqlFreeResult());
	methods.push_back(new MysqlGetClientInfo());
	methods.push_back(new MysqlGetFieldName());
	methods.push_back(new MysqlGetFieldValue());
	methods.push_back(new MysqlInfo());
	methods.push_back(new MysqlInit());
	methods.push_back(new MysqlNextResult());
	methods.push_back(new MysqlNextRow());
	methods.push_back(new MysqlNumFields());
	methods.push_back(new MysqlNumRows());
	methods.push_back(new MysqlPing());
	methods.push_back(new MysqlQuery());
	methods.push_back(new MysqlRealEscapeString());
	methods.push_back(new MysqlRealConnect());
	methods.push_back(new MysqlSelectDB());
	methods.push_back(new MysqlStat());
	methods.push_back(new MysqlStoreResult());
	methods.push_back(new MysqlUseResult());
}


}
}
}
