#!/usr/local/bin/oscript

public object BaseObject {
	protected int mProtectedValue;
}

public object DerivedObject extends BaseObject {
	public void setValue(int value ) modify {
		mProtectedValue = value;
	}
}

public void Main(int argc, string args) {
	DerivedObject do = new DerivedObject();
	do.setValue(173);

	//do.mProtectedValue = 1389;
}

