#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string args)
	{
		writeln("getenv Test");

		writeln("getenv(\"OBJECTIVESCRIPT_LIBRARY\") = " + getenv("OBJECTIVESCRIPT_LIBRARY"));
		writeln("getenv(bla) = " + getenv("bla"));
	}
}

