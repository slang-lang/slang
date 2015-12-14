#!/usr/bin/oscript

import System.Console;

public object Main
{
	private Console mConsole;

	public void Main(Number argc, String argv)
	{
		mConsole = new Console();
/*
		print("Hello World!");
		print("argc = " & argc);
		print("argv = " & argv);
*/

		/*System.*/mConsole.write("Hello ");
		/*System.*/Console.writeln("World!");
		/*System.*/Console.write("argc = " & argc);
		/*System.*/Console.writeln("argv = " & argv);
	}
}
