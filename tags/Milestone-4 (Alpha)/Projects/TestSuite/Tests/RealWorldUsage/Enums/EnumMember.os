#!/usr/local/bin/oscript

public enum Enum {
	Label1 = 0,
	Label2 = 1,
	Label3 = 2;
}

public object EnumMember {
	public Enum mEnum;

	public void Constructor(Enum e const) {
		mEnum = e;
	}
}

public void Main(int argc, string args) {
	EnumMember m = new EnumMember(Enum.Label2);

	print("m.mEnum = " + string m.mEnum);

	switch ( m.mEnum ) {
		case Enum.Label1: { print("Label1"); break; }
		case Enum.Label2: { print("Label2"); break; }
		case Enum.Label3: { print("Label3"); break; }
		default: { print("default"); break; }
	}
}

