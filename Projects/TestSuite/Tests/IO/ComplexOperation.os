#!/usr/local/bin/oscript

public object Main
{
	public void Main(int argc, string argv)
	{
		assert( writeFile() );
		assert( readFile() );
	}

	private bool readFile() const
	{
		int fd = 0;
		int result = 0;

		try {
			fd = fopen("file.complex", "r");

			write("file: ");

			bool boolValue = freadb(fd);		// read bool
			write("bool " + boolValue + ", ");

			double doubleValue = freadd(fd);	// read double
			write("double " + doubleValue + ", ");

			float floatValue = freadf(fd);		// read float
			write("float " + floatValue + ", ");

			int intValue = freadi(fd);		// read int
			write("int " + intValue + ", ");

			string stringValue = freads(fd, 6);	// read string
			write("string " + stringValue);

/*
			write(", string ");
			for ( int i = 0; i < 7; i=i+1) {
				string str = freads(fd, 1);	// read string
				write(str);
			}
*/

			writeln("");
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
			fwrites(fd, "1731389");  // write string
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

