#!/usr/local/bin/oscript

public namespace ArrayTest
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			array<number> values;// = [1, 3, 5];

			print("values.size() = " + values.size());

			return true;
		}
	}
}

