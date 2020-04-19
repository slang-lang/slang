#!/usr/local/bin/slang

public void Main(int argc = 0, string argv = "") {
	print("argc = " + argc);
	print("argv = " + argv);

	print("DefaultParameter();");
	DefaultParameter();
	print("DefaultParameter(2);");
	DefaultParameter(2);
}

private void DefaultParameter(int param = 1) {
	print("param = " + param);
}

