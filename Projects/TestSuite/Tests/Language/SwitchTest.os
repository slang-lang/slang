#!/usr/local/bin/oscript

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			assert( TestCase4() );
			assert( TestCase5() );
		}

		private bool TestCase1() const
		{
			print("TestCase 1");

			int one = 1;
			switch ( one ) {
				case 1: return true;
				default: return false;
			}

			return false;
		}

		private bool TestCase2() const
		{
			print("TestCase 2");

			int one = 1;
			switch ( one + 2 ) {
				case 1: return false;
				case 2: return false;
				case 3: return true;
				default: return false;
			}

			return false;
		}

		private bool TestCase3() const
		{
			print("TestCase 3");

			int one = 1;
			switch ( one ) {
				case 1: print("case 1"); print("some other commands"); print("bla");
				case 2: print("case 2"); break;
				case 3: assert( false ); break;
				default: assert( false ); break;
			}

			return true;
		}

		private bool TestCase4() const {
			print("TestCase 4");

			int one  = 1;
			switch ( one ) {
				case 0: return false;
				default: return true;
			}

			return false;
		}

		private bool TestCase5() const
		{
			print("TestCase 5");

			int one = 1;
			switch ( 2 ) {
				case (one + 1): print("case one + 1"); return true;
				case 2: print("case 2"); return true;
			}

			return false;
		}
	}

