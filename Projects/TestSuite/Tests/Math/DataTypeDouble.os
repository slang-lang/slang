#!/usr/local/bin/slang

public void Main(int argc = 0, string argv = "") {
	double value = 100000000000000000000d;
	print("value = " + value);

	double mNumber = 1.731389d;

	print("mNumber = " + mNumber);

	//assert( (string mNumber) == "1.731389" );
	assert( mNumber == 1.731389d );
}

