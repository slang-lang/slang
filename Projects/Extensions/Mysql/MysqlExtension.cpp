
// Header
#include "MysqlExtension.h"

// Library includes

// Project includes
#include "MysqlAffectedRows.h"
#include "MysqlClose.h"
#include "MysqlDataSeek.h"
#include "MysqlErrno.h"
#include "MysqlError.h"
#include "MysqlFieldCount.h"
#include "MysqlFieldSeek.h"
#include "MysqlFieldTell.h"
#include "MysqlFreeResult.h"
#include "MysqlGetClientInfo.h"
#include "MysqlGetFieldName.h"
#include "MysqlGetFieldValue.h"
#include "MysqlInfo.h"
#include "MysqlInit.h"
#include "MysqlNextResult.h"
#include "MysqlNextRow.h"
#include "MysqlNumFields.h"
#include "MysqlNumRows.h"
#include "MysqlPing.h"
#include "MysqlQuery.h"
#include "MysqlRealConnect.h"
#include "MysqlRealEscapeString.h"
#include "MysqlSelectDB.h"
#include "MysqlStat.h"
#include "MysqlStoreResult.h"
#include "MysqlUseResult.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


MysqlExtension::MysqlExtension()
: AExtension("Mysql")
{
}

void MysqlExtension::provideMethods(ExtensionMethods &methods)
{
	assert(methods.empty());

	methods.push_back(new MysqlAffectedRows());
	methods.push_back(new MysqlClose());
	methods.push_back(new MysqlDataSeek());
	methods.push_back(new MysqlErrno());
	methods.push_back(new MysqlError());
	methods.push_back(new MysqlFieldCount());
	methods.push_back(new MysqlFieldSeek());
	methods.push_back(new MysqlFieldTell());
	methods.push_back(new MysqlFreeResult());
	methods.push_back(new MysqlGetClientInfo());
	methods.push_back(new MysqlGetFieldName());
	methods.push_back(new MysqlGetFieldValueByIndex());
	methods.push_back(new MysqlGetFieldValueByName());
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
