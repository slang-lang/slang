#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		writeln("mysql_real_connect()");

		mysql_real_connect("192.168.0.22", 3306, "oscript", "oscript", "ts_parking");

		writeln("done");
	}
}

