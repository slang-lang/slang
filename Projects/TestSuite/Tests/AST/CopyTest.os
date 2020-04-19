#!/usr/local/bin/slang

private object CopyObject {
	public int mValue;

	public void Constructor(int value) {
		mValue = value;
	}

	public CopyObject Copy() const {
		print("Copy operator");
		return new CopyObject(mValue);
	}
}

public void Main(int argc, string args) {
	CopyObject obj1 = new CopyObject(173);
	CopyObject obj2 = copy obj1;

	assert( obj1 != obj2 );
}

