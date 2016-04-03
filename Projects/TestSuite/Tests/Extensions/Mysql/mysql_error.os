#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		writeln("mysql_error() = " + mysql_error());
		writeln("done.");
	}
}

