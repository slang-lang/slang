#!/usr/local/bin/oscript

import Mysql.All;

public object Main {
	public void Main(int argc = 0, string args = "") {
		Mysql.MysqlDebugMode = true;

		Mysql.Connection conn = new Mysql.Connection("192.168.0.23", 0, "oscript", "oscript", "ts_parking");
		if ( !conn.isOpen() ) {
			print("error while connecting to database!");
			exit(1);
		}

		Mysql.Query query = conn.createQuery();
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
			Mysql.Result result = query.execute();

			while ( result.hasNext() ) {
				result.next();

				Mysql.Row row = result.getCurrentRow();
				print(row.ToString());
			}
		}
		catch {
			print("caught exception!");
		}
		finally {
			print("finally");
		}
	}
}

