#!/usr/local/bin/oscript

import Mysql.All;

public void Main(int argc, string args) {
	try {
		Mysql.Connection conn = new Mysql.Connection("0.0.0.0", 0, "root", "");
		if ( !conn.isOpen() ) {
			writeln("error while opening Mysql connection: " + conn.error());
			return;
		}

		if ( conn.selectDB("ts_parking") != 0 ) {
			writeln("error while selecting database!");
			return;
		}

		Mysql.MysqlDebugMode = true;

		//conn.settings().setAutoEscaping(true);	// caining is not supported (yet)
		Mysql.Settings s = conn.settings();
		s.setAutoEscaping(true);

		writeln(conn.stat());

		Mysql.Result result = conn.query("Select * from parking_zones");

		writeln("result.numRows() = " + result.numRows());
		writeln("result.numFields() = " + result.numFields());

		while ( result.hasNext() ) {
			result.next();

			Mysql.Row row = result.getCurrentRow();
			writeln(row.toString());
		}

		conn.close();
	}
	catch ( string e ) {
		print(e);
	}
}

