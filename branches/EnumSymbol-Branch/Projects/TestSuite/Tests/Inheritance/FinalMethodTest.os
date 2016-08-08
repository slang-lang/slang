#!/usr/local/bin/oscript

private object BaseObject {
	public string ToString() const final {
		return "BaseObject";
	}
}

private object DerivedObject extends BaseObject {
	public string ToString() const final {
		return "DerivedObject";
	}
}

public object Main {
	public void Main(int argc = 0, string args = "") {
		DerivedObject derived = new DerivedObject();

		string result = derived.ToString();
		print("result = " + result);

		assert( result == "BaseObject" );
	}
}

