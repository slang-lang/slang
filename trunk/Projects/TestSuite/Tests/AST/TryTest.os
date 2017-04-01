#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
}

private bool TestCase1() throws {
	print("TestCase 1: try");

	int blocks;
	try {
		blocks++;

		print("try-block");
		throw;

		assert( false );
	}

	print("after try-block");

	return blocks == 1;
}

private bool TestCase2()  throws {
	print("TestCase 2: try-finally");

	int blocks;
	try {
		blocks++;

		print("try-block");
		throw;

		assert( false );
	}
	finally {
		blocks++;

		print("finally-block");
	}

	return blocks == 2;
}

private bool TestCase3() throws {
	print("TestCase 3: try-catch");

	int blocks;
	try {
		blocks++;

		print("try-block");
		throw;
	}
	catch {
		blocks++;

		print("catch-block");
	}

	print("after catch-block");
	return blocks == 2;
}

private bool TestCase4() throws {
	print("TestCase 4: try-catch-finally");

	int blocks;
	try {
		blocks++;

		print("try");

		throw new string("this is an exception");
	}
	catch ( int e ) {
		print("catch(int): " + e);

		assert( false );
	}
	catch ( string e ) {
		blocks++;

		print("catch(string): " + e);

		return true;
	}
	finally {
		blocks++;

		print("finally");

		assert( blocks == 3 );
	}

	assert( !"after return" );
	return false;
}

