#!/usr/local/bin/oscript

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			assert( TestCase1() );
			assert( TestCase2() );
			assert( TestCase3() );
			//assert( TestCase4() );
		}

		private bool TestCase1() const
		{
			int one = 1;
			switch ( one ) {
				case 1: return true;
				default: return false;
			}

			return false;
		}

		private bool TestCase2() const
		{
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
			int one = 1;
			switch ( one ) {
				case 1: print("case 1");
				case 2: print("case 2"); break;
				case 3: assert( false ); break;
				default: assert( false ); break;
			}

			return true;
		}

		private bool TestCase4() const
		{
			int one = 1;
			switch ( 2 ) {
				case (one + 1): print("case one + 1"); break;
				case 2: print("case 2"); break;
			}

			return true;
		}
	}

