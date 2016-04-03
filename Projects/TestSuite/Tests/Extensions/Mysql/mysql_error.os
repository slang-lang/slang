#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		writeln("mysql_error(0) = " + mysql_error(/*dummy handle*/0));
		writeln("done.");
	}
}

