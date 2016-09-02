#!/usr/local/bin/oscript

import System.Collections.DoubleLinkedList;
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
		print("TestCase 1: push_back");

		try {
			System.DoubleLinkedList list = new System.DoubleLinkedList();

			TestObject item;
			item = new TestObject(173);
			list.push_back(Object item);

			item = new TestObject(1389);
			list.push_back(Object item);

			// Usage
			assert( list.size() == 2 );

			item = list.at(0);
			assert(item.mValue == 173);

			item = list.at(1);
			assert(item.mValue == 1389);

			return true;
		}
		catch ( System.OutOfBoundsException e ) {
			print(e.what());
			return false;
		}

		return false;
	}
}

