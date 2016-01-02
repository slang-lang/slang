#!/usr/local/bin/oscript

public namespace FinalTest
{
	public object Main
	{
		private number mNumber final;

		public void Main(number argv = 0, string args = "")
		{
			mNumber = 1;

			assert( TestCase1() );
		}

		private bool TestCase1()
		{
/*
			number one const = 1;
			one = 2;	// throws ConstCorrectnessViolated exception
*/

			mNumber = 2;	// throws ConstCorrectnessViolated exception

			return false;
		}
	}
}
