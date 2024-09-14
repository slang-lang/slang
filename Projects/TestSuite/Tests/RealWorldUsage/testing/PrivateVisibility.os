#!/usr/local/bin/slang

public object BaseObject {
	private int mPrivateValue;
}

public object DerivedObject extends BaseObject {
	public void setValue(int value ) modify {
		mPrivateValue = value;
	}
}

public void Main(int argc, string args) {
	//BaseObject bo = new BaseObject();
	//bo.mPrivateValue = 173;

	DerivedObject do = new DerivedObject();
	do.setValue(173);
}

