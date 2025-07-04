#!/usr/bin/env slang

import System.Collections.Stack;
import System.Exception;
import System.Integer;
import System.String;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	//assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );
	assert( TestCase9() );
	assert( TestCase10() );

	print( "passed" );
}

private bool TestCase1() const {
	print("TestCase 1: push");

	try {
		var stack = new Stack<String>();

		String item;

		item = new String("664");
		stack.push(item);

		item = new String("173");
		stack.push(item);

		item = new String("1389");
		stack.push(item);

		// Usage
		assert( stack.size() == 3 );

		item = String stack.at(0);
		assert( item == "664" );

		item = String stack.at(1);
		assert( item == "173" );

		item = String stack.at(2);
		assert( item == "1389" );

		assert( stack.size() == 3 );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());

		return false;
	}

	return false;
}

private bool TestCase2() const {
	print("TestCase 2: pop");

	try {
		var stack = new Stack<String>();

		// Setup
		String item;

		item = new String("664");
		stack.push(item);

		item = new String("173");
		stack.push(item);

		item = new String("1389");
		stack.push(item);

		// Usage
		assert( stack.size() == 3 );

		item = String stack.at(0);
		assert( item == "664" );

		item = String stack.at(1);
		assert( item == "173" );

		item = String stack.at(2);
		assert( item == "1389");

		stack.pop();

		assert( stack.size() == 2 );

		item = String stack.at(0);
		assert( item == "664" );

		item = String stack.at(1);
		assert( item == "173" );

		stack.pop();

		assert( stack.size() == 1 );

		item = String stack.at(0);
		assert( item == "664" );

		stack.pop();

		assert( stack.size() == 0 );
		assert( stack.empty() );

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
		return false;
	}

	return false;
}

private bool TestCase3() const {
	print("TestCase 3: iterate");

	try {
		var stack = new Stack<String>();

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );

		var it = stack.getIterator();

		it.next();
		assert( "1" == string it.current() );

		it.next();
		assert( "2" == string it.current() );

		it.next();
		assert( "3" == string it.current() );

		it.reset();
		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		return true;
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
	}

	return false;
}

private bool TestCase4() const {
	print("TestCase 4: reverse iterate");

	try {
		var stack = new Stack<String>();

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );

		var it = stack.getReverseIterator();

		it.next();
		assert( "3" == string it.current() );

		it.next();
		assert( "2" == string it.current() );

		it.next();
		assert( "1" == string it.current() );

		it.reset();
		while ( it.hasNext() ) {
			it.next();

			//print(it.current());
		}

		return true;
	}
	
	return false;
}

private bool TestCase5() const {
	print("TestCase 5: indexOf");

	try {
		var stack = new Stack<String>();

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );

		assert( stack.indexOf(new String("1")) == 0 );
		assert( stack.indexOf(new String("2")) == 1 );
		assert( stack.indexOf(new String("3")) == 2 );

		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase 6: contains");

	try {
		Stack<Integer> stack = new Stack<Integer>();
		assert( stack is Object );
		assert( stack is ICollection );

		stack.push(new Integer(1));
		stack.push(new Integer(2));
		stack.push(new Integer(3));

		assert( stack.size() == 3 );

		assert( stack.contains(new Integer(1)) );
		assert( stack.contains(new Integer(2)) );
		assert( stack.contains(new Integer(3)) );

		return true;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: peek");

	try {
		Stack<Integer> stack = new Stack<Integer>();
		assert( stack is Object );
		assert( stack is ICollection );

		stack.push(new Integer(1));
		assert( stack.peek() == 1 );

		stack.push(new Integer(2));
		assert( stack.peek() == 2 );

		stack.push(new Integer(3));
		assert( stack.peek() == 3 );

		assert( stack.size() == 3 );

		assert( stack.contains(new Integer(1)) );
		assert( stack.contains(new Integer(2)) );
		assert( stack.contains(new Integer(3)) );

		return true;
	}

	return false;
}

private bool TestCase8() const {
	print("TestCase 8: native types");

	try {
		var stack = new Stack<int>();
		assert( stack is ICollection );

		stack.push( 1 );
		assert( stack.peek() == 1 );

		stack.push( 2 );
		assert( stack.peek() == 2 );

		assert( stack.size() == 2 );

		assert( stack.contains( 2 ) );
		assert( stack.contains( 1 ) );

		return true;
	}

	return false;
}

private bool TestCase9() const {
	print("TestCase 9: foreach");

	try {
		var stack = new Stack<int>();
		assert( stack is ICollection );

		stack.push( 1 );
		stack.push( 2 );

		foreach ( int i : stack ) {
			//print("i = " + i);
		}

		return true;
	}

	return false;
}

private bool TestCase10() const {
	print( "TestCase 10: erase and add" );

	try {
		var collection = new Stack<int>();

		// Set up
		collection.push( 1 );
		collection.push( 2 );
		collection.push( 3 );

		// Test
		assert( collection.size() == 3 );

		collection.erase( 0 );

		assert( collection.size() == 2 );
		collection.erase( 0 );
		assert( collection.size() == 1 );

		collection.erase( 0 );
		assert( collection.size() == 0 );

		collection.push( 4 );

		assert( collection.at( 0 ) == 4 );

		return true;
	}

	return false;
}

