#!/usr/local/bin/oscript

private object BaseObject {
	private void Constructor() { }

	public string ToString() const final {
		return "BaseObject";
	}
}

private object DerivedObject extends BaseObject {
	private void Constructor() { }

	public string ToString() const {
		return "DerivedObject";
	}
}

public void Main(int argc = 0, string args = "") {
	DerivedObject derived = new DerivedObject();

	string result = derived.ToString();
	print("result = " + result);

	assert( result == "BaseObject" );
}

