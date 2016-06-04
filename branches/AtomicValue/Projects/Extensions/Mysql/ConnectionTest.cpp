
// Header
#include "ConnectionTest.h"

// Library includes
#include <mysql.h>
#include <stdio.h>

// Project includes
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Utils/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace Mysql {


ConnectionTest::ConnectionTest()
: Runtime::Method(0, "mysql_connection_test", Designtime::VoidObject::TYPENAME)
{
	ParameterList params;

	setSignature(params);
}

Runtime::ControlFlow::E ConnectionTest::execute(const ParameterList& params, Runtime::Object* result, const TokenIterator& token)
{
	(void)params;
	(void)result;
	(void)token;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "192.168.0.22";
	char *user = "oscript";
	char *password = "oscript";
	char *database = "ts_parking";

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	/* send SQL query */
	if (mysql_query(conn, "select * from parking_zones")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	/* output table name */
	printf("MySQL Tables in mysql database:\n");

	unsigned int num_fields = 0;
	num_fields = mysql_num_fields(res);

	while ((row = mysql_fetch_row(res)) != NULL) {
		unsigned long *lengths = mysql_fetch_lengths(res);

		for ( unsigned int i = 0; i < num_fields; i++ ) {
			printf("[%.*s]", (int) lengths[i], row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);

	return Runtime::ControlFlow::Normal;
}


}
}
}
