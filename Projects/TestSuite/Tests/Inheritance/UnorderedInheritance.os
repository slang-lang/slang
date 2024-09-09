#!/usr/local/bin/slang

private object DerivedObject extends BaseObject {
	public void Constructor() {
		print("DerivedObject.Constructor");

		base.Constructor();
	}

	public void Destructor() {
		print("DerivedObject.Destructor");

		base.Destructor();
	}
}

public void Main(int argc = 0, string args = "") {
	DerivedObject derived = new DerivedObject();
}

private object BaseObject {
	public void Constructor() {
		print("BaseObject.Constructor");
	}

	public void Destructor() {
		print("BaseObject.Destructor");
	}
}

