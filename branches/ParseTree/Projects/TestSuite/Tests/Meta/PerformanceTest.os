#!/usr/local/bin/oscript

public int Main(int argc = 0, string args = "") {
	int lowerbound = 1;
	int upperbound = 100000;

	print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

	while ( lowerbound < upperbound ) {
		print("lowerbound = " + lowerbound);

		//lowerbound = lowerbound + 1;
		//lowerbound += 1;
		lowerbound++;
	}

	print("Finished performance test.");

	return 0;
}

