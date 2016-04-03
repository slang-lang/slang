
#ifndef ObjectiveScript_Extensions_MySQL_Types_h
#define ObjectiveScript_Extensions_MySQL_Types_h


// Library includes
#include <map>
#include <mysql.h>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


typedef std::map<int, MYSQL*> MysqlConnectionMap;
typedef std::map<int, MYSQL_RES*> MysqlResultMap;

extern MysqlConnectionMap mMysqlConnections;
extern int mNumMysqlConnections;

extern MysqlResultMap mMysqlResults;
extern int mNumMysqlResults;


}
}
}


#endif
