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
	List list = new List();

	// Setup
	list.push_back(Object new Integer(664));
	list.push_back(Object new Integer(173));
	list.push_back(Object new Integer(1389));

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
	List list = new List();

	// Setup
	string item;

	item = "664";
	list.push_back(Object item);

	item = "173";
	list.push_back(Object item);

	item = "1389";
	list.push_back(Object item);

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

