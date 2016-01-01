#!/usr/local/bin/oscript

public namespace PerformanceTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			print("Starting performance test...");

			number count = 0;
			number upperbound = 10000;

			while ( count < upperbound ) {
				//print("count = " + count);
				count = count + 1;
			}

			print("Finished performance test.");
		}
	}
}

