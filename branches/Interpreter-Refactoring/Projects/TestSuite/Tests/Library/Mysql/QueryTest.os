#!/usr/local/bin/oscript

import Mysql.All;

public object Main {
	public void Main(int argc = 0, string args = "") {
		MysqlQueryTest();
	}

	private bool MysqlQueryTest() modify {
		Mysql.MysqlDebugMode = true;

		Mysql.Connection conn = new Mysql.Connection("0.0.0.0", 0, "root", "", "ts_parking");
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
			if ( !result ) {
				print("error while executing query");
				exit(4);
			}

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

		return true;
	}
}

