#!/usr/bin/env slang

public object BaseObject {
	protected int mPublicNumber;	// public members are not allowed, remember the "Law of Demeter"
	protected int mProtectedNumber;
	private int mPrivateNumber;

	public void Constructor() {
		mPublicNumber = 1;
		mProtectedNumber = 2;
		mPrivateNumber = 3;
	}

	public string ToString() const {
		return "mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
	}
}

public object DerivedObject extends BaseObject {
	private int mPrivateNumber;

	public void Constructor() {
		base.Constructor();
	}

	public int GetBox() const {
		return 1;
	}

	public string GetIdentifier() const {
		return "bla";
	}

	public string ToString2() const {
		return base.ToString() + "	mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
	}

	public void test() modify {
		mPublicNumber = 2;
		mProtectedNumber = 2;
		mPrivateNumber = 2;
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject d = new DerivedObject();

	print(d.ToString());
	print(d.ToString2());

	d.test();

	print(d.ToString());
	print(d.ToString2());
}

