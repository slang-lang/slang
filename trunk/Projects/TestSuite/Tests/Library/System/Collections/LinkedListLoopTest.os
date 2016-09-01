#!/usr/local/bin/oscript

import System.Collections.LinkedList;
import System.Exception;

private int LOOP const = 1000;

private object TestObject {
	private int mValue;

	public void TestObject(int value) {
		mValue = value;
	}

	public string ToString() const {
		return "mValue = " + mValue;
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		print("LinkedList loop test");

		try {
			ObjectMethod();
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
		}
	}
}

private void ObjectMethod() {
	System.LinkedList list = new System.LinkedList();

	// Setup
	TestObject item;

	item = new TestObject(664);
	list.push_back(Object item);

	item = new TestObject(173);
	list.push_back(Object item);

	item = new TestObject(1389);
	list.push_back(Object item);

	// Usage
	assert( list.size() == 3 );

	int count = 0;

	while ( count < LOOP ) {
		count++;
		list.reset();

		//print("Loop " + count);

		while ( list.hasNext() ) {
			list.next();

			TestObject item = TestObject list.current();
			//print(item.ToString());
		}
	}
}

private void ValueMethod() {
	System.LinkedList list = new System.LinkedList();

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
		list.reset();

		//print("Loop " + count);

		while ( list.hasNext() ) {
			list.next();

			Object item = list.current();
			//print(item);
		}
	}
}

