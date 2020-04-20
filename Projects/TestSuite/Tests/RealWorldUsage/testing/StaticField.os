#!/usr/local/bin/slang

public object StaticField {
	public static int Value;
}

public object OuterNestedObject {
	public object InnerNestedObject {
		public static int StaticValue;
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

