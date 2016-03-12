#!/usr/local/bin/oscript

public namespace ThisTest
{
	public object Main
	{
		private int mNumber;

		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
		}

		private bool TestCase1() const
		{
			print("TestCase1()");

			print(this);

			return true;
		}
		
		private bool TestCase2() modify
		{
			print("TestCase2()");

			mNumber = 1;
			print("mNumber = " + mNumber);
			assert( mNumber == 1 );

			print("this.mNumber = " + this.mNumber);
			assert( this.mNumber == 1 );

			return true;
		}

		private bool TestCase3() modify
		{
			print("TestCase3()");

			mNumber = 1;
			assert( mNumber == 1 );

			ModifyThisInMethod1(2);
			assert( mNumber == 2);

			ModifyThisInMethod2(3);
			assert( mNumber == 3 );

			this.mNumber = 4;
			assert( mNumber == 4 );

			return true;
		}

		private void ModifyThisInMethod1(int value) modify
		{
			mNumber = value;
		}

		private void ModifyThisInMethod2(int value) modify
		{
			this.mNumber = value;
		}
	}
}
