#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
}

private bool TestCase1() {
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

private bool TestCase2()  {
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

private bool TestCase3() {
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

private bool TestCase4() {
	print("TestCase 4: try-catch-finally");

	int blocks;
	try {
		blocks++;

		print("try");

		throw "this is an exception";
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

private bool TestCase5() {
	print("TestCase 5: try-catch");

	int blocks;
	try {
		blocks++;
		print("try");

		return true;
	}
	catch ( int e ) {
		assert( !"this will never happen" );
	}

	return false;
}

private bool TestCase6() {
	print("TestCase 6: throw without matching catch");

	try {
		TestCase6ThrowingMethod();

		assert( false );
	}
	catch ( int e ) {
		print("e: " + e);
	}

	return true;
}

private void TestCase6ThrowingMethod() throws {
	try {
		throw 42;
	}
	catch ( string e ) {
		print("e: " + e);
		assert( false );
	}

	assert( false );
}

