#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		int file = 0;
		int result = 0;

		try {
			file = fopen("file.double", "ctw");
			writeln("handle: " + file);

			result = fwrited(file, 17.0d);
			writeln("result = " + result);
		}
		catch {
			writeln("error during fwrite");
		}
		finally {
			result = fclose(file);
			writeln("result = " + result);
		}
	}
}

