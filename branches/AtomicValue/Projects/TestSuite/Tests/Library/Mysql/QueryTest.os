#!/usr/local/bin/oscript

import Mysql.All;

public object Main {
	public void Main(int argc = 0, string args = "") {
		MysqlDebugMode = true;

		Connection conn = new Connection("192.168.0.23", 0, "oscript", "oscript", "ts_parking");
		if ( !conn.isOpen() ) {
			print("error while connecting to database!");
			exit(1);
		}

		Query query = conn.createQuery();
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

		//print(conn.stat());

		try {
			Result result = query.execute();

			while ( result.hasNext() ) {
assert(0);
				result.next();

assert(0);
				Row row = result.getCurrentRow();
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

