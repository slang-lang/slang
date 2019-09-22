#!/usr/local/bin/oscript

public object StaticMethod {
	public int Value static;

	public int getValue() const static {
		return StaticMethod.Value;
	}

	public void setValue(int value) modify static {
		StaticMethod.Value = value;
	}
}

public void Main(int argc, string args) {
	StaticMethod.Value = 173;
	print("StaticMethod.Value: " + StaticMethod.getValue());
	StaticMethod.setValue(1389);
	print("StaticMethod.Value: " + StaticMethod.getValue());
}

