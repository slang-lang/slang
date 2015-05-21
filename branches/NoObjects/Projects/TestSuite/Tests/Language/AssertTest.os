
import system.assert;

public namespace
{
	private object Main
	{
		public void Main()
		{
			assert(true);
			assert(false == false);
			assert(ReturnOne());
			assert(ReturnOne() > 0);
			assert(ReturnOne() & "bla");
			assert(ReturnAString());
			assert(ReturnTrue());
			//assert(!ReturnFalse());	// unary operator ! is not yet implemented
			assert(ReturnFalse());
		}

		private String ReturnAString() const
		{
			return "ThisIsAString";
		}

		private Number ReturnOne() const
		{
			return 1;
		}

		private Bool ReturnFalse() const
		{
			return false;
		}

		private Bool ReturnTrue() const
		{
			return true;
		}
	}
}
