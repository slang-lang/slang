#!/usr/local/bin/oscript

public namespace ListTest
{
	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
		}

		private bool TestCase1() const
		{
			list<int> values;

			print("values.size() = " + values.size());

			values.push_back(5);
			values.push_back(17);

			print("values.size() = " + values.size());

			return true;
		}
	}
}
