#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		int error = 0;
		int handle = 0;

		handle = mysql_init();
		writeln("mysql_init() = " + handle);



		writeln("done.");
	}
}

