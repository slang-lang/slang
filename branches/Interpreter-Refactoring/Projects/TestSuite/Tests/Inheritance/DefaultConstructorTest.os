#!/usr/local/bin/oscript

private object BaseObject {
	public void BaseObject() {
		print("BaseObject()");
	}

	public void ~BaseObject() {
		print("~BaseObject()");
	}
}

private object DerivedObject extends BaseObject {
	public void DerivedObject() {
		print("DerivedObject()");
	}

	public void ~DerivedObject() {
		print("~DerivedObject()");
	}
}

public void Main(int argc = 0, string argv = "") {
	DerivedObject derived = new DerivedObject();
}

