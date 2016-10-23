#!/usr/local/bin/oscript

import System.Collections.List;

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
	TestObject item;

	item = new TestObject(664);
	list.push_back(Object item);

	item = new TestObject(173);
	list.push_back(Object item);

	item = new TestObject(1389);
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

			TestObject item = TestObject it.current();
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

