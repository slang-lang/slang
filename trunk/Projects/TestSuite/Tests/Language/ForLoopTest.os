#!/usr/local/bin/oscript

import system.assert;

public namespace 
{
	public object Main
	{
		//private Assert mAssert;

		public void Main(Number argc = 0, String argv = "")
		{
			//mAssert = new Assert();

			for ( Number loop1 = 0; loop1 < 5; loop1 = loop1 + 1; ) {
				print("loop1 = " & loop1);
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert(loop1 == 5);
			//mAssert.debug(loop1 == 5, "loop1 == 5");

			for ( Number loop2 = 0; loop2 < 10; loop2 = loop2 + 1; ) {
				print("loop2 = " & loop2);
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert(loop2 == 10);
			//mAssert.debug(loop2 == 10), "loop2 == 10)");

			//delete mAssert;
		}
	}
}
