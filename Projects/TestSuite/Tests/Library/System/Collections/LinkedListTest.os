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
	}

	private bool TestCase1() modify {
		print("TestCase 1");

		try {
			System.LinkedList list = new System.LinkedList();

			TestObject obj1 = new TestObject(173);
			list.push(Object obj1);

			TestObject obj2 = new TestObject(1389);
			list.push(Object obj2);

			// Usage
			assert( list.size() == 2 );

			while ( list.hasNext() ) {
				list.next();

				TestObject item = TestObject list.current();
				print(item.ToString());
			}
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return true;
		}

		return false;
	}
}

