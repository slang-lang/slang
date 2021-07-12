#!/usr/local/bin/slang

public object TestObject {
	public string Value;

	public TestObject operator>>( string other ) modify {
		print("operator>>");

		Value += other;

		return this;
	}
}

public void Main(int argc = 0, string args = "") {
	TestObject obj = new TestObject();

	obj >> "0664";
	obj >> "173";
	obj >> "1389";

	assert( obj.Value == "06641731389" );
}

