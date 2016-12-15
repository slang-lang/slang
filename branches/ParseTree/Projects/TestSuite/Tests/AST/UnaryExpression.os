#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	int a = -1;
	bool b = !true;
//	int c = ++1;
//	int d = 1++;
	int e = 1 + 2 * (2 - (-3));
	int f = e + 2;
	int g = MethodCall(e, f);
//	int h = bool e;
}

private int MethodCall(int i = 173, int j = 1389) {
	print("\"MethodCall(\"" + i + "\", \"" + j + "\")\"");
	return i + j;
}

