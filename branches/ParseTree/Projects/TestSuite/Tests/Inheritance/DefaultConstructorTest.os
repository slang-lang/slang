#!/usr/local/bin/oscript

private object BaseObject {
	public void Constructor() {
		print("BaseObject.Constructor()");
	}

	public void Destructor() {
		print("BaseObject.Destructor()");
	}
}

private object DerivedObject extends BaseObject {
	public void Constructor() {
		print("DerivedObject.Constructor()");
	}

	public void Destructor() {
		print("DerivedObject.Destructor()");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject();
}

