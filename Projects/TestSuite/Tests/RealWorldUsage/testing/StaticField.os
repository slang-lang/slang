#!/usr/local/bin/slang

public object StaticField {
	public int Value static;
}

public object OuterNestedObject {
	public object InnerNestedObject {
		public int StaticValue static;
	}
}

public void Main(int argc, string args) {
	StaticField.Value = 173;
	print("StaticField.Value = " + StaticField.Value);

	OuterNestedObject.InnerNestedObject.StaticValue = 1389;
	print("OuterNestedObject.InnerNestedObject.StaticValue = " + OuterNestedObject.InnerNestedObject.StaticValue);

	StaticField fieldObj = new StaticField();
	print("fieldObj.Value = " + fieldObj.Value);
}

