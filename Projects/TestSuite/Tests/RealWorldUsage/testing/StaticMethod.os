#!/usr/local/bin/slang

public object StaticMethod {
	public static int Value;

	public static int getValue() const {
		return StaticMethod.Value;
	}

	public static stable void setValue(int value) modify {
		StaticMethod.Value = value;
	}
}

public void Main(int argc, string args) {
	StaticMethod.Value = 173;
	print("StaticMethod.Value: " + StaticMethod.getValue());
	StaticMethod.setValue(1389);
	print("StaticMethod.Value: " + StaticMethod.getValue());
}

