#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		int file = 0;
		int result = 0;

		try {
			file  = fopen("file.bin", "crt");
			writeln("handle: " + file);

			result = fclose(file);
			writeln("result = " + result);
		}
		catch {
			writeln("error during fopen");
		}
	}
}
