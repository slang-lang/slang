#!/usr/local/bin/oscript

public namespace OutterSpace {
	public object InnerObject {
		private int mValue;

		public void Constructor(int value) {
			mValue = value;
		}

		public int getValue() const {
			return mValue;
		}
	}
}

public int gIntValue = 173;
public OutterSpace.InnerObject gSpacedObject;

public void Main(int argc = 0, string args = "") {
	assert( TestCase1() );
	assert( TestCase2() );	// not supported by now (and maybe never)
}

private bool TestCase1() const {
	print("TestCase 1: global atomic variable definition");

	return gIntValue == 173;
}

private bool TestCase2() const {
	print("TestCase 2: global namespaced variable definition");

	gSpacedObject = new OutterSpace.InnerObject(173);

	return gSpacedObject.getValue() == 173;
}

