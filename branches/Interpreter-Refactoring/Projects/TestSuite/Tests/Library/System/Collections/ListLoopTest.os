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
	System.List list = new System.List();

	// Setup
	Integer item;

	item = new Integer(664);
	list.push_back(Object item);

	item = new Integer(173);
	list.push_back(Object item);

	item = new Integer(1389);
	list.push_back(Object item);

	// Usage
	assert( list.size() == 3 );

	System.Iterator it = list.getIterator();

	int count = 0;

	while ( count < LOOP ) {
		count++;
		it.reset();

		//print("Loop " + count);

		while ( it.hasNext() ) {
			it.next();

			Integer item = Integer it.current();
			//print(item.ToString());
		}
	}
}

private void ValueMethod() {
	System.List list = new System.List();

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

	System.Iterator it = list.getIterator();

	int count = 0;

	while ( count < LOOP ) {
		count++;
		it.reset();

		//print("Loop " + count);

		while ( it.hasNext() ) {
			it.next();

			Object item = it.current();
			//print(item);
		}
	}
}

