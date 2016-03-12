#!/usr/local/bin/oscript

public object Main
{
	public void Main(number argc = 0, string argv = "")
	{
		int lowerbound = 1;
		int upperbound = 100000;

		print("Starting performance test (by counting from " + lowerbound + " to " + upperbound + ")...");

		while ( lowerbound < upperbound ) {
			//print("lowerbound = " + lowerbound);
			//lowerbound += 1;
			lowerbound = lowerbound + 1;
		}

		print("Finished performance test.");
	}
}

