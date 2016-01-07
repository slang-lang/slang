#!/usr/local/bin/oscript

public namespace HelloWorld
{
	public object Main
	{
		public void Main(number argc, string argv)
		{
			print("Hello World!");
			print("argc = " + argc);
			print("argv = " + argv);
		}
	}
}
