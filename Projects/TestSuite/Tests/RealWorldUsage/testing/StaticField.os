#!/usr/local/bin/slang

public object StaticField {
	public static int Value;
}

public object OuterNestedObject {
	public object InnerNestedObject {
		public static int StaticValue;
	}
}

public void Main(int argc, string args) modify {
	StaticField.Value = 173;
	print("StaticField.Value = " + StaticField.Value);

	OuterNestedObject.InnerNestedObject.StaticValue = 1389;
	print("OuterNestedObject.InnerNestedObject.StaticValue = " + OuterNestedObject.InnerNestedObject.StaticValue);

	StaticField fieldObj = new StaticField();
	print("fieldObj.Value = " + fieldObj.Value);	// this throws an exception, but it should not be seen as valid by the parser in the firts place
}

