#!/usr/local/bin/oscript

import System.Collections.Stack;
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
}

private bool TestCase1() const {
	print("TestCase 1: push");

	try {
		System.Stack stack = new System.Stack();

		String item;

		item = new String("664");
		stack.push(Object item);

		item = new String("173");
		stack.push(Object item);

		item = new String("1389");
		stack.push(Object item);

		// Usage
		assert( stack.size() == 3 );

		item = String stack.at(0);
		assert( item.mValue == "664" );

		item = String stack.at(1);
		assert( item.mValue == "173" );

		item = String stack.at(2);
		assert( item.mValue == "1389" );

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
		System.Stack stack = new System.Stack();

		// Setup
		String item;

		item = new String("664");
		stack.push(Object item);

		item = new String("173");
		stack.push(Object item);

		item = new String("1389");
		stack.push(Object item);

		// Usage
		assert( stack.size() == 3 );

		item = String stack.at(0);
		assert( item.mValue == "664" );

		item = String stack.at(1);
		assert( item.mValue == "173" );

		item = String stack.at(2);
		assert( item.mValue == "1389");

		stack.pop();

		assert( stack.size() == 2 );

		item = String stack.at(0);
		assert( item.mValue == "664" );

		item = String stack.at(1);
		assert( item.mValue == "173" );

		stack.pop();

		assert( stack.size() == 1 );

		item = String stack.at(0);
		assert( item.mValue == "664" );

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
		System.Stack stack = new System.Stack();

		stack.push(Object new String("1"));
		stack.push(Object new String("2"));
		stack.push(Object new String("3"));

		assert( stack.size() == 3 );

		System.Iterator it = stack.getIterator();

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
		System.Stack stack = new System.Stack();

		stack.push(Object new String("1"));
		stack.push(Object new String("2"));
		stack.push(Object new String("3"));

		assert( stack.size() == 3 );

		System.ReverseIterator it = stack.getReverseIterator();

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
		System.Stack stack = new System.Stack();

		stack.push(Object new String("1"));
		stack.push(Object new String("2"));
		stack.push(Object new String("3"));

		assert( stack.size() == 3 );

		assert( stack.indexOf(Object new String("1")) == 0 );
		assert( stack.indexOf(Object new String("2")) == 1 );
		assert( stack.indexOf(Object new String("3")) == 2 );

		return true;
	}

	return false;
}

private bool TestCase6() const {
	print("TestCase 6: contains");

	try {
		System.Stack stack = new System.Stack();
		assert( stack is Object );
		assert( stack is System.AbstractCollection );

		stack.push(Object new Integer(1));
		stack.push(Object new Integer(2));
		stack.push(Object new Integer(3));

		assert( stack.size() == 3 );

		assert( stack.contains(Object new Integer(1)) );
		assert( stack.contains(Object new Integer(2)) );
		assert( stack.contains(Object new Integer(3)) );

		return true;
	}

	return false;
}

private bool TestCase7() const {
	print("TestCase 7: peek");

	try {
		System.Stack stack = new System.Stack();
		assert( stack is Object );
		assert( stack is System.AbstractCollection );

		stack.push(Object new Integer(1));
		assert( stack.peek() == 1 );

		stack.push(Object new Integer(2));
		assert( stack.peek() == 2 );

		stack.push(Object new Integer(3));
		assert( stack.peek() == 3 );

		assert( stack.size() == 3 );

		assert( stack.contains(Object new Integer(1)) );
		assert( stack.contains(Object new Integer(2)) );
		assert( stack.contains(Object new Integer(3)) );

		return true;
	}

	return false;
}
