#!/usr/local/bin/oscript

import System.Collections.GenericIterator;
import System.Collections.GenericStack;
import System.Exception;
import System.Integer;
import System.String;

public void Main(int argc = 0, string args = "") const {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
	assert( TestCase6() );
	assert( TestCase7() );
	assert( TestCase8() );
	assert( TestCase9() );
	assert( TestCase10() );
}

private bool TestCase1() const {
	print("TestCase 1: push");

	try {
		GenericStack<String> stack = new GenericStack<String>();

		stack.push(new String("664"));
		stack.push(new String("173"));
		stack.push(new String("1389"));

		// Usage
		assert( stack.size() == 3 );

		GenericIterator<String> it = stack.getIterator();
		while ( it.hasNext() ) {
			it.next();

			//print(string it.current());
		}

		assert( stack.at(0) == "664" );
		assert( stack.at(1) == "173" );
		assert( stack.at(2) == "1389" );

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
		GenericStack<String> stack = new GenericStack<String>();

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

		item = stack.at(0);
		assert( item == "664" );

		item = stack.at(1);
		assert( item == "173" );

		item = stack.at(2);
		assert( item == "1389");

		stack.pop();

		assert( stack.size() == 2 );

		item = stack.at(0);
		assert( item == "664" );

		item = stack.at(1);
		assert( item == "173" );

		stack.pop();

		assert( stack.size() == 1 );

		item = stack.at(0);
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
		GenericStack<String> stack = new GenericStack<String>();

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );

		GenericIterator<String> it = stack.getIterator();

		it.next();
		assert( it.current() == "1" );

		it.next();
		assert( it.current() == "2" );

		it.next();
		assert( it.current() == "3" );

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
		GenericStack<String> stack = new GenericStack<String>();

		stack.push(new String("1"));
		stack.push(new String("2"));
		stack.push(new String("3"));

		assert( stack.size() == 3 );

		GenericReverseIterator<String> it = stack.getReverseIterator();

		it.next();
		assert( it.current() == "3" );

		it.next();
		assert( it.current() == "2" );

		it.next();
		assert( it.current() == "1" );

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
		GenericStack<String> stack = new GenericStack<String>();

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
		GenericStack<Integer> stack = new GenericStack<Integer>();
		assert( stack is Object );
		assert( stack is IGenericCollection );
		assert( stack is IIterateable );
		assert( stack is GenericStack<Integer> );

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
		GenericStack<Integer> stack = new GenericStack<Integer>();
		assert( stack is Object );
		assert( stack is GenericStack<Integer> );

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
	print("TestCase 8: atomic type");

	try {
		GenericStack<int> stack = new GenericStack<int>();

		stack.push(1);
		assert( stack.peek() == 1 );

		stack.push(2);
		assert( stack.peek() == 2 );

		stack.push(3);
		assert( stack.peek() == 3 );

		GenericIterator<int> it = stack.getIterator();

		while ( it.hasNext() ) {
			it.next();

			//print(it.current());
		}
	}

	return true;
}

private bool TestCase9() const {
	print("TestCase 9: clear");

	try {
		GenericStack<int> stack = new GenericStack<int>();

		stack.push(1);
		stack.push(2);
		stack.push(3);

		assert( stack.size() == 3 );

		GenericIterator<int> it = stack.getIterator();

		while ( it.hasNext() ) {
			it++;

			//print(it.current());
		}

		stack.clear();

		assert( stack.size() == 0 );
		assert( stack.empty() );

		return true;
	}

	return false;
}

private bool TestCase10() const {
	print("TestCase 10: foreach");

	try {
		GenericStack<int> stack = new GenericStack<int>();

		stack.push(1);
		stack.push(2);
		stack.push(3);

		assert( stack.size() == 3 );

		foreach ( int i : stack ) {
			//print(i);
		}

		return true;
	}

	return false;
}

