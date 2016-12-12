#!/usr/local/bin/oscript

public void Main(int argc, string args) {
	int a = -1;
	bool b = !true;
	int c = ++1;
	int d = 1++;
	int e = 1 + 2 * (2 - (-3));
	int f = e + 2;
	int g = MethodCall(e, f);
	int h = bool e;
}

private int MethodCall(int i, int j) {
	print("\"MethodCall(\"" + i + "\", \"" + j + "\")\"");
	return i + j;
}

