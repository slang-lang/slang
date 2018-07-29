#!/usr/local/bin/oscript

import Mysql.All;

public void Main(int argc, string args) {
	try {
		MysqlConnection conn = new MysqlConnection("0.0.0.0", 0, "root", "");
		if ( !conn.isOpen() ) {
			writeln("error while opening Mysql connection: " + conn.error());
			return;
		}

		if ( conn.selectDB("ts_parking") != 0 ) {
			writeln("error while selecting database!");
			return;
		}

		//conn.settings().setAutoEscaping(true);	// chaining is not supported
		MysqlSettings s = conn.settings();
		s.setAutoEscaping(true);

		writeln(conn.stat());

		MysqlResult result = conn.query("Select * from parking_zones");

		writeln("result.numRows() = " + result.numRows());
		writeln("result.numFields() = " + result.numFields());

		while ( result.hasNext() ) {
			result.next();

			MysqlRow row = result.getCurrentRow();
			writeln(row.toString());
		}

		conn.close();
	}
	catch ( string e ) {
		print("caught exception: " + e);
	}
}

