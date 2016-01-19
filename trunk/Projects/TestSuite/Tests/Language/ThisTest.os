#/usr/local/bin/oscript

public namespace ThisTest
{
	public object Main
	{
		private number mNumber;

		public void Main(number argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
		}

		private bool TestCase1() const
		{
			print(this);

			return true;
		}
		
		private bool TestCase2() modify
		{
			mNumber = 1;
			print("mNumber = " + mNumber);
			print("this.mNumber = " + this.mNumber);

			return true;
		}
	}
}
