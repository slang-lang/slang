#!/usr/local/bin/oscript

/*
public object Main {
	public void Main(int argc = 0, string argv = "") {
		int lowerbound = 1;
		int upperbound = 100000;

		print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

		while ( lowerbound < upperbound ) {
			//print("lowerbound = " + lowerbound);

			//lowerbound = lowerbound + 1;
			lowerbound = lowerbound++;
		}

		print("Finished performance test.");
	}
}
*/


public int Main(int argc = 0, string args = "") modify {
	int lowerbound = 1;
	int upperbound = 100000;

	print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

	while ( lowerbound < upperbound ) {
		//print("lowerbound = " + lowerbound);

		//lowerbound = lowerbound + 1;
		lowerbound = lowerbound++;
	}

	print("Finished performance test.");

	return 0;
}

