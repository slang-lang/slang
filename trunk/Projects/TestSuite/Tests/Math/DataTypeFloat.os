#!/usr/local/bin/oscript

public namespace Math
{
	public object Main
	{
		private float mNumber;

		public void Main(number argc = 0, string argv = "")
		{
			mNumber = 1.f;

			print("mNumber = " + mNumber);

			assert( mNumber == 1.f );
		}
	}
}
