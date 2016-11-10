#!/usr/local/bin/oscript

private object TestObject {
	public int operator[](int index) const {
		return index;
	}
}

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
}

private bool TestCase1() const {
	print("TestCase 1: index operator");

	TestObject obj = new TestObject();

	print(string obj[173]);

	return obj[173] == 173;
}
