#!/usr/local/bin/oscript

public namespace Math
{
	public object Main
	{
		private number mNumber;

		public void Main(int argc = 0, string argv = "")
		{
			mNumber = 1.0;

			print("mNumber = " + mNumber);

			assert( mNumber == 1.0 );
		}
	}
}
