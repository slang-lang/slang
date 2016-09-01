#!/usr/local/bin/oscript

import System.Collections.LinkedList;
import System.Exception;

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
		assert( TestCase1() );
		assert( TestCase2() );
		assert( TestCase3() );
		assert( TestCase4() );
		assert( TestCase5() );
	}

	private bool TestCase1() modify {
		print("TestCase 1: push_back");

		try {
			System.LinkedList list = new System.LinkedList();

			// Setup
			TestObject obj;

			obj = new TestObject(173);
			list.push_back(Object obj);

			obj = new TestObject(1389);
			list.push_back(Object obj);

			// Usage
			assert( list.size() == 2 );

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase2() modify {
		print("TestCase 2: push_front");

		try {
			System.LinkedList list = new System.LinkedList();

			TestObject obj;

			obj = new TestObject(2);
			list.push_front(Object obj);

			obj = new TestObject(1);
			list.push_front(Object obj);

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}

			return true;
		}

		return false;
	}

	private bool TestCase3() modify {
		print("TestCase 3: insert");

		try {
			System.LinkedList list = new System.LinkedList();

			// Setup
			TestObject obj;

			obj = new TestObject(0664);
			list.insert(Object obj, 0);

			obj = new TestObject(1389);
			list.insert(Object obj, 1);

			obj = new TestObject(173);
			list.insert(Object obj, 1);

			// Usage
			assert( list.size() == 3 );

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}

	private bool TestCase4() modify {
		print("TestCase 4: erase first");

		try {
			System.LinkedList list = new System.LinkedList();

			// Setup
			TestObject obj;

			obj = new TestObject(0664);
			list.insert(Object obj, 0);

			obj = new TestObject(1389);
			list.insert(Object obj, 1);

			obj = new TestObject(173);
			list.insert(Object obj, 1);

			// Usage
			assert( list.size() == 3 );

			list.erase(0);

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}

			assert( list.size() == 2 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}


	private bool TestCase5() modify {
		print("TestCase 5: erase middle");

		try {
			System.LinkedList list = new System.LinkedList();

			// Setup
			TestObject obj;

			obj = new TestObject(0664);
			list.insert(Object obj, 0);

			obj = new TestObject(1389);
			list.insert(Object obj, 1);

			obj = new TestObject(173);
			list.insert(Object obj, 1);

			// Usage
			assert( list.size() == 3 );

			list.erase(1);

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}

			assert( list.size() == 2 );

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}
}

