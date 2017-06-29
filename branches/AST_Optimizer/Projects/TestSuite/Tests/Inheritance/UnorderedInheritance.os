#!/usr/local/bin/oscript

private object DerivedObject extends BaseObject {
	public void Constructor() {
		print("Constructor");
	}

	public void Destructor() {
		print("Destructor");
	}
}

public void Main(int argc = 0, string args = "") {
	DerivedObject derived = new DerivedObject();
}

private object BaseObject {
	public void Constructor() {
		print("Constructor");
	}

	public void Destructor() {
		print("Destructor");
	}
}

