#!/usr/local/bin/slang

private object BaseObject {
	public string ToString() const final {
		return "BaseObject";
	}
}

private object DerivedObject extends BaseObject {
	public string ToString() const {
		return "DerivedObject";
	}
}

public void Main(int argc = 0, string args = "") {
	DerivedObject derivedObj = new DerivedObject();

	string result = derivedObj.ToString();
	print("result = " + result);

	assert( result == "BaseObject" );
}

