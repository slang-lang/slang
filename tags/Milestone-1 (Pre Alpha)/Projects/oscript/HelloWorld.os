#!/usr/local/bin/oscript

public namespace Program
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			print("Hello World!");
			print("argc = " & argc);
			print("argv = " & argv);
		}
	}
}
