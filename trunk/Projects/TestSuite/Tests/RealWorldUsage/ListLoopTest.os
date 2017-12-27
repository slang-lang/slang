#!/usr/local/bin/oscript

import System.Collections.List;
import System.Integer;

private int LOOP const = 1000;

public void Main(int argc = 0, string args = "") {
	print("LinkedList loop test");

	try {
		ObjectMethod();
	}
	catch ( OutOfBoundsException e ) {
		print(e.what());
	}
}

private void ObjectMethod() {
	List<Integer> list = new List<Integer>();

	// Setup
	list.push_back(new Integer(664));
	list.push_back(new Integer(173));
	list.push_back(new Integer(1389));

	// Usage
	assert( list.size() == 3 );

	int count = 0;
	Integer item;

	while ( count < LOOP ) {
		count++;

		//print("Loop " + count);

		foreach ( Integer item : list ) {
			//print(item.ToString());
		}
	}
}

private void ValueMethod() {
	List<string> list = new List<string>();

	// Setup
	list.push_back("0664");
	list.push_back("173");
	list.push_back("1389");

	// Usage
	assert( list.size() == 3 );

	int count = 0;

	while ( count < LOOP ) {
		count++;

		//print("Loop " + count);

		foreach ( string item : list ) {
			//print(item);
		}
	}
}

