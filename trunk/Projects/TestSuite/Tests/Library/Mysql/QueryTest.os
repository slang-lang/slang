#!/usr/local/bin/oscript

import Mysql.All;

public void Main(int argc = 0, string args = "") modify {
	MysqlQueryTest();
}

private bool MysqlQueryTest() modify {
	MysqlConnection conn = new MysqlConnection("0.0.0.0", 0, "root", "", "ts_parking");
	if ( !conn.isOpen() ) {
		print("error while connecting to database!");
		exit(1);
	}

	MysqlQuery query = conn.createQuery();
	if ( !query ) {
		print("error while creating query!");
		exit(2);
	}

	query.prepare("SELECT * FROM parking_tickets WHERE valid_thru >= :valid_thru");

	bool bind = query.bind(":valid_thru", "2016-01-01");
	if ( !bind ) {
		print("error while binding string");
		exit(3);
	}

	query.prepare("Select * from parking_zones");

	print(conn.stat());

	try {
		MysqlResult result = query.execute();
		if ( !result ) {
			print("error while executing query");
			exit(4);
		}

		while ( result.hasNext() ) {
			result.next();

			MysqlRow row = result.getCurrentRow();
		}

		return true;
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}

	return false;
}

