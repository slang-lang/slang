#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		writeln("mysql_info(0) = " + mysql_info(/*dummy handle*/0));
		writeln("done.");
	}
}

