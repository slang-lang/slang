#!/usr/local/bin/oscript

public void Main(int argc = 1, string args = "") {
	int i = 1 + 2 + (3 + 4) * (5 + 6);

	print("i = " + i);

	i += 5 * 3;

	print("i = " + i);
}

