#!/usr/local/bin/slang

public void Main(int argc, string args) {
	int ref_i ref = new int(0);

	print("ref_i = " + ref_i);

	increment(ref_i);

	print("ref_i = " + ref_i);

	//int value = new int(0);
	int value = 173;

	increment(value);
}

private void increment(int value ref) {
	print("increment(" + value + ")");

	value++;
}

