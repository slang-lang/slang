#!/usr/local/bin/slang

import Mysql.All;

public void Main(int argc, string args) modify {
	try {
		MysqlConnection conn = new MysqlConnection("0.0.0.0", 3306, "root", "");
		if ( !conn.isOpen() ) {
			print("error while opening Mysql connection: " + conn.error());
			return;
		}

		if ( !conn.selectDB("ts_parking") ) {
			print("error while selecting database!");
			return;
		}

		MysqlSettings s = conn.settings();
		s.setAutoEscaping(true);

		print(conn.stat());

		MysqlResult result = conn.query("Select * from parking_zones");

		print("result.numRows() = " + result.numRows());
		print("result.numFields() = " + result.numFields());

		while ( result.hasNext() ) {
			MysqlRow row = result.next();

			print(row.toString());
		}

		conn.close();
	}
	catch ( string e ) {
		print("Exception: " + e);
	}
	catch ( IException e ) {
		print("Exception: " + e.what());
	}
}

