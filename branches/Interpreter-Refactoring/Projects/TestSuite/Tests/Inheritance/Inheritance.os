#!/usr/local/bin/oscript

public object BaseObject {
	protected int mPublicNumber;	// public members are not allowed, remember the "Law of Demeter"
	protected int mProtectedNumber;
	private int mPrivateNumber;

	public void BaseObject() {
		mPublicNumber = 1;
		mProtectedNumber = 1;
		mPrivateNumber = 1;
	}

	public string ToString() const {
		return "mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
	}
}

public object DerivedObject extends BaseObject {
	//private int mPrivateNumber;

	public void Main(int argc = 0, string argv = "") {
		base.BaseObject();

		print(ToString());
		print(ToString2());

		test();

		print(ToString());
		print(ToString2());
	}

	public int GetBox() const {
		return int(1);
	}

	public string GetIdentifier() const {
		return "bla";
	}

	public string ToString2() const {
		return base.ToString() + "	mPublicNumber = " + mPublicNumber + ", mProtectedNumber = " + mProtectedNumber + ", mPrivateNumber = " + mPrivateNumber;
	}

	private void test() modify {
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

