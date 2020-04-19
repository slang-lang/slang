#!/usr/local/bin/slang

public void Main(int argc, string args) {
	assert( TestCase1() );
}

private bool TestCase1() throws {
	print("TestCase 1: rethrow exception");

	try {
		print("outer try");

		try {
			print("inner try");

			print("inner throw");
			throw "this is a new string exception";
		}
		catch ( string e ) {
			print("inner catch");

			print("inner re-throw");
			throw;
		}
	}
	catch ( string e ) {
		print("outer catch: " + e);
		return true;
	}

	return false;
}

