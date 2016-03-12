#!/usr/local/bin/oscript

public namespace ObjectEqualityTest
{
	private object TestObject
	{
		private int mValue;

		public int getValue() const
		{
			return mValue;
		}

		public void setValue(int value const)
		{
			mValue = value;
		}

/*
		public bool operator==(TestObject other const) const
		{
			return mValue == other.mValue;
		}
*/
	}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
		}

		private bool TestCase1() const
		{
			print("TestCase 1: comparing different references");

			TestObject obj1 = new TestObject();
			TestObject obj2 = new TestObject();
			
			return obj1 != obj2;
		}

		private bool TestCase2() const
		{
			print("TestCase 2: comparing same references");

			TestObject obj1 = new TestObject();
			
			return obj1 == obj1;
		}
	}
}
