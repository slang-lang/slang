#!/usr/bin/env slang

public void Main(int argc = 1, string args = "") {
	int count = 0;

	while ( count < 5 ) {
		print("loop count = " + count);

		count += 1;
	}

	count = 0;

	while ( count < 5 )
		count += 1;

	print("count = " + count);
}

