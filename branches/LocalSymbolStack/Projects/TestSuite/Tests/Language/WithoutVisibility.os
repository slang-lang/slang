#!/usr/local/bin/oscript

/*
enum Enum1 {
	Monday = 0,
	Tuesday;
}
*/

object TestObject {
	int mValue;

	void Constructor(int value) {
		print("value = " + value);
		mValue = value;
	}
}

int mMember = 42;

int getMember() const {
	return mMember;
}

public void Main(int argc, string args) {
	TestObject obj = new TestObject(173);

	print("mMember = " + string getMember());
}

