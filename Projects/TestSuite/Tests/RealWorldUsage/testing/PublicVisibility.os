#!/usr/local/bin/slang

public object BaseObject {
	public int mPublicValue;
}

public object DerivedObject extends BaseObject {
	public void setValue(int value ) modify {
		mPublicValue = value;
	}
}

public void Main(int argc, string args) {
	DerivedObject do = new DerivedObject();
	do.setValue(173);

	do.mPublicValue = 1389;
}

