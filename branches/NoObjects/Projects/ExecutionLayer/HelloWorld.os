#!/usr/bin/oscript

import System.Console;

public namespace 
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			print("Hello World!");
			print("argc = " & argc);
			print("argv = " & argv);

			System.Console.writeln("");
			System.Console.write("Hello World!");
			System.Console.writeln("Hello World!");
			System.Console.write("argc = " & argc);
			System.Console.writeln("argv = " & argv);
		}
	}
}
