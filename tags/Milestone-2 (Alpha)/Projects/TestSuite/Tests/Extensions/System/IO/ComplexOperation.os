#!/usr/local/bin/oscript

//import System.IO.File;
//import System.IO.All;
import System.All;

public object Main
{
	public void Main(int argc, string argv)
	{
		File file = new File("file.complex", "ctw");
		assert( file.isOpen() );

		assert( writeFile() );
		assert( readFile() );
	}

	private bool readFile() const
	{
		int fd = 0;
		int result = 0;

		try {
			fd = fopen("file.complex", "r");

			bool boolValue = freadb(fd);		// read bool
			writeln("bool " + boolValue + ", ");

			double doubleValue = freadd(fd);	// read double
			writeln("double " + doubleValue + ", ");

			float floatValue = freadf(fd);		// read float
			writeln("float " + floatValue + ", ");

			int intValue = freadi(fd);		// read int
			writeln("int " + intValue + ", ");

			string stringValue = freads(fd, 6);	// read string
			writeln("string " + stringValue);
		}
		catch {
			writeln("ups..");
		}
		finally {
			result = fclose(fd);

			if ( result != 0 ) {
				writeln("error while closing file");
			}
		}

		return true;
	}

	private bool writeFile() const
	{
		int fd = 0;
		int result = 0;

		try {
			fd = fopen("file.complex", "ctw");

			fwriteb(fd, true);	// write bool
			fwrited(fd, 173.1389d); // write double
			fwritef(fd, 173.1389f)  // write float
			fwritei(fd, 1731389);	// write int
			fwrites(fd, "1731389");	// write string
		}
		catch {
			writeln("ups..");
		}
		finally {
			result = fclose(fd);

			if ( result != 0 ) {
				writeln("error while closing file");
			}
		}

		return true;
	}
}
