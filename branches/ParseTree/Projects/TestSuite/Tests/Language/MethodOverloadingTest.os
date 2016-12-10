#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	returnVoid();

	int i = 0;
	i = testMethod(returnNumber(1), returnNumber(2));
	print("i = " + i);

	i = returnSum(2, 3);
	print("i = " + i);

	i = returnSum(3, 4, 5);
	print("i = " + i);

	string s = returnSum("6+", "7");
	print("s = " + s);

	s = returnSum("" + 8, "9");
	print("s = " + s);
}

private int returnNumber(int param1) const {
	return param1;
}

private int returnSum(int p1, int p2) const {
	return p1 + p2;
}

private int returnSum(int p1, int p2, int p3) const {
	return p1 + p2 + p3;
}

private string returnSum(string p1, string p2) const {
	return "" + p1 + p2;
}

private void returnVoid() {
	print("method without parameters called which returns nothing");
	return;
}

private int testMethod(int param1, int param2) const {
	return param1 + param2;
}

