#!/usr/local/bin/oscript

public object Level1Object {
	public int mPublicValue;
	protected int mProtectedValue;
	derived int mDerivedValue;
	private int mPrivateValue;

	public void Constructor() {
		print("mPublicValue = " + mPublicValue);
		print("mProtectedValue = " + mProtectedValue);
		print("mDerivedvalue = " + mDerivedValue);
		//print("mPrivateValue = " + mPrivateValue);
	}
}

public object Level2Object extends Level1Object {
	public void Constructor() {
		base.Constructor();

		print("mPublicValue = " + mPublicValue);
		print("mProtectedValue = " + mProtectedValue);
		print("mDerivedvalue = " + mDerivedValue);
		//print("mPrivateValue = " + mPrivateValue);
	}
}

public object Level3Object extends Level2Object {
	public void Constructor() {
		base.Constructor();

		print("mPublicValue = " + mPublicValue);
		print("mProtectedValue = " + mProtectedValue);
		//print("mDerivedvalue = " + mDerivedValue);
		//print("mPrivateValue = " + mPrivateValue);
	}
}

public void Main(int argc, string args) {
	Level3Object l3 = new Level3Object();

	print("Level3Object.mPublicValue = " + l3.mPublicValue);
	//print("Level3Object.mProtectedValue = " + l3.mProtectedValue);
	//print("Level3Object.mDerivedValue = " + l3.mDerivedValue);
	//print("Level3Object.mPrivateValue = " + l3.mPrivateValue);
}

