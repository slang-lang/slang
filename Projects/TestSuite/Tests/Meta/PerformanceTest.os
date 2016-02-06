#!/usr/local/bin/oscript

public namespace PerformanceTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			number count = 1;
			number upperbound = 100000;

			print("Starting performance test (by counting from " + count + " to " + upperbound + ")...");

			while ( count < upperbound ) {
				//print("count = " + count);
				count = count + 1;
			}

			print("Finished performance test.");
		}
	}
}

