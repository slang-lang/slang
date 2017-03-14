#!/usr/local/bin/oscript

import System.Integer;

private object TestObject {
	private int mValue;

	private void Constructor(int value) {
		mValue = value;
	}

	public string ToString() const {
		return "TestObject={ mValue=" + mValue + " }";
	}

	public bool operator==(int other) const {
		print("operator==(int)");
		return mValue == other;
	}
	public bool operator==(TestObject other) const {
		print("operator==(TestObject)");
		return mValue == other.mValue;
	}

	public void operator=(int other) modify {
		print("operator=(int)");
		mValue = other;
	}

	public int =operator(int value) const {
		print("int " + mValue + " =operator(int " + value + ")");
		return mValue;
	}

	public string =operator(string value) const {
		print("string =operator(string " + value + ")");
		return string mValue;
	}

	public void operator+(int other) modify {
		print("operator+");
		mValue = mValue + other;
	}
/*
	public int +operator(int other) const {
		print("int +operator(int " + other + ")");
		return mValue;
	}
	public string +operator(string other) const {
		print("string +operator(string " + other + ")");
		return string mValue;
	}

	public int -operator(int other) const {
		print("int -operator(int " + other + ")");
		return mValue;
	}
*/
	public void operator++() modify {
		print("operator++");
		mValue = mValue++;
	}

	public void ++operator() modify {
		print("++operator");
		mValue = mValue++;
	}

	public int <operator(int value) const {
		print("<operator(int " + value + ")");
		return mValue;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );
	assert( TestCase3() );
	assert( TestCase4() );
	assert( TestCase5() );
}

private bool TestCase1() const {
	print("TestCase 1: classic operator");

	TestObject obj = new TestObject(1);
	print(obj.ToString());

	obj++;

	print(obj.ToString());

	return obj == 2;
}

private bool TestCase2() const {
	print("TestCase 2: modern operator");

	TestObject obj = new TestObject(1);
	print(obj.ToString());

	obj=++obj;

	print(obj.ToString());

	return obj == 2;
}

private bool TestCase3() const {
	print("TestCase 3: modern value operator");

	TestObject obj = new TestObject(1);
	print(obj.ToString());

	int value = obj;

	print("value = " + value);

	return value == 1;
}

private bool TestCase4() const {
	print("TestCase 4: modern + operator");

	TestObject obj = new TestObject(1);
	print(obj.ToString());

	int value = 5 + int obj;

	print("value = " + value);

	return value == 6;
}

private bool TestCase5() const {
	print("TestCase 5: modern compare operator");

	TestObject obj = new TestObject(1);
	print(obj.ToString());

	int value = 4;
	print("value = " + value);

	print("value == obj: " + (value == obj));
	print("value > obj: " + (value > obj));
	print("value >= obj: " + (value >= obj));
	print("value < obj: " + (value < obj));
	print("value <= obj: " + (value <= obj));

	print("value - 3 == obj: " + (value - 3 == obj));
	print("value == obj + 3: " + (value == obj + 3));
	print("value == 8 - obj: " + (value == 8 - int obj));

	print("obj = " + 1 + string obj);

	return bool obj;
}

