#!/usr/local/bin/oscript

import System.Collections.List;

private object Item {
	public Object mNext;
	public Object mPrevious;
	public int mValue;

	public void Constructor(int value, Object previous, Object next) {
		mNext = next;
		mPrevious = previous;
		mValue = value;

		print("constructing " + typeid(this) + "(" + mValue + ")");
	}

	public void Destructor() {
		print("destructing " + typeid(this) + "(" + mValue + ")");
	}

	public string =operator(string none) const {
		string result = "{ ";

		result += "mPrevious: ";
		if ( mPrevious ) {
			result += typeid(mPrevious);
		}
		else {
			result += "(" + typeid(mPrevious) + ")null";
		}

		result += ", mNext: ";
		if ( mNext ) {
			result += typeid(mNext);
		}
		else {
			result += "(" + typeid(mNext) + ")null";
		}

		result += ", mValue: " + mValue + " }";

		return result;
	}
}

public void Main(int argc, string args) {
	try {
		List list = new List();

		Item item1 = new Item(1, null, null);
		Item item2 = new Item(2, Object item1, null);
		Item item3 = new Item(3, Object item2, null);

		item1.mNext = Object item2;
		item2.mNext = Object item3;

		list.push_back(Object item1);
		list.push_back(Object item2);
		list.push_back(Object item3);

		foreach ( Item i : list ) {
			print("" + string i);
		}
	}
}

