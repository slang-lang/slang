#!/usr/local/bin/oscript

public namespace ArrayTest
{
	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			array<int> values;// = [1, 3, 5];

			print("values.size() = " + values.size());

			return true;
		}
	}
}

