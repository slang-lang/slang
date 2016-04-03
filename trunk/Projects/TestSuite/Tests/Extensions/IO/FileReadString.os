#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		int file = 0;
		int result = 0;

		try {
			file = fopen("file.string", "r");
			writeln("handle: " + file);

			string text = freads(file, 3);
			write("freads = " + text);

			text = freads(file, 1);
			write(text);

			text = freads(file, 10);
			writeln(text);
		}
		catch {
			writeln("error during fread");
		}
		finally {
			result = fclose(file);
			writeln("fclose = " + result);
		}
	}
}

