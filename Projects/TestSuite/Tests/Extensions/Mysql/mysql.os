#!/usr/local/bin/oscript

import Mysql.Connection;

public object Main
{
	public void Main(int argc, string argv)
	{
		mysql_init();

		assert( TestCase1() );
	}

	private bool TestCase1() modify
	{
		Connection conn = new Connection();

		conn.open("192.168.0.22", 3306, "oscript", "oscript", "ts_parking");
		if ( !conn.isOpen() ) {
			writeln("error: could not connect to database!);
			throw new string("error: could not connect to database!);
		}

		// do something
		//writeln("conn.info() = " + conn.info());

		conn.close();

		return true;
	}
}

