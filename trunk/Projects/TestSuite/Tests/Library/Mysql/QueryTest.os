#!/usr/local/bin/oscript

import Mysql.All;

public object Main {
	public void Main(int argc = 0, string args = "") {
		Connection conn = new Connection("192.168.0.23", 0, "oscript", "oscript", "ts_parking");
		if ( !conn.isOpen() ) {
			print("error while connecting to database!");
			exit(1);
		}

		Query query = new Query(conn);
		if ( !query ) {
			print("error while creating query!");
			exit(2);
		}

		query.prepare("SELECT * FROM parking_tickets WHERE valid_thru >= :valid_thru");
		print(query.ToString());
		query.bind(":valid_thru", "2016-05-21");
		print(query.ToString());

		query.execute();
	}
}

