#!/usr/local/bin/oscript

import LinkedStackOfStrings;
import System.Collections.Iterator;
import System.String;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
}

private bool TestCase1() {
	print("TestCase 1");

	LinkedStackOfStrings<String> stack = new LinkedStackOfStrings<String>();

	assert( stack.isEmpty() );

	stack.push(new String("1"));
	stack.push(new String("2"));
	stack.push(new String("3"));

	assert( stack.size() == 3 );
	assert( stack.peek() == "3" );

	assert( stack.pop() == "3" );
	assert( stack.size() == 2 );

	assert( stack.pop() == "2" );
	assert( stack.size() == 1 );

	assert( stack.pop() == "1" );
	assert( stack.isEmpty() );

	return true;
}

private bool TestCase2() {
	print("TestCase 2");

	try {
		LinkedStackOfStrings<String> stack = new LinkedStackOfStrings<String>();

		assert( stack.isEmpty() );

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );
		assert( stack.peek() == "3" );

		System.Iterator it = stack.getIterator();
		while ( it.current() ) {
			print(string it.current());

			if ( !it.hasNext() ) {
				break;
			}

			it.next();
		}

		return true;
	}
	catch ( string e ) {
		print(e);
	}
	catch ( IOException e ) {
		print( "IOException: " + e.what());
	}
	finally {
		print("finally!");
	}
	catch ( OutOfBoundsException e ) {
		print( "OutOfBoundsException: " + e.what() );
	}
	catch ( Exception e ) {
		print("caught generic exception: " + e.what());
	}

	return false;
}

private bool TestCase3() {
	print("TestCase 3: foreach");

	try {
                LinkedStackOfStrings<String> stack = new LinkedStackOfStrings<String>();

                assert( stack.isEmpty() );

                stack.push(new String("1"));
                stack.push(new String("2"));
                stack.push(new String("3"));

		assert( !stack.isEmpty() );
		assert( stack.size() == 3 );

		foreach ( String s : stack ) {
			print(s);
		}

		return true;
	}

	return false;
}

