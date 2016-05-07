#!/usr/local/bin/oscript

import Mysql.All;

public object Main {
	public void Main(int argc, string args) {
		Connection conn = new Connection("192.168.0.22", 3306, "oscript", "oscript", "ts_parking");
		if ( !conn.isOpen() ) {
			writeln("error while opening Mysql connection: " + conn.error());
			return;
		}

		MysqlDebugMode = true;

		//conn.settings().setAutoEscaping(true);
		Settings s = conn.settings();
		s.setAutoEscaping(true);

		Result result = conn.query("Select * from parking_zones");

		writeln("result.NumRows() = " + result.NumRows());
		writeln("result.NumFields() = " + result.NumFields());

		while ( result.HasNext() ) {
			result.Next();

			Row row = result.GetCurrentRow();
			writeln(row.ToString());

			//Entry e = result.GetField(0);
			//writeln("e = " + e.ToString());
		}

		conn.close();
	}
}

