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
			assert( TestCase6() );
		}

		private bool TestCase1() const
		{
			for ( int loop1 = 0; loop1 < 5; loop1 = loop1 + 1 ) {
				print("loop1 = " + loop1);
				assert( loop1 < 5 );
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert( loop1 == 5 );

			return true;
		}
		private bool TestCase2() const
		{
			for ( int loop2 = 0; loop2 < 10; loop2 = loop2 + 1 ) {
				print("loop2 = " + loop2);
				assert( loop2 < 10 );
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert( loop2 == 10 );

			return true;
		}

		private bool TestCase3() const
		{
			for ( int loop3 = 0; loop3 < 5; loop3 = loop3 + 1 ) {
				print("loop3 = " + loop3);
				assert( loop3 < 5 );

				if ( loop3 > 2 ) {
					break;
				}
			}

			print("loop3 = " + loop3);
			assert( loop3 == 3 );

			return true;
		}

		private bool TestCase4() const 
		{
			for ( int loop4 = 0; loop4 < 10; loop4 = loop4 + 1 ) {
				print("loop4 = " + loop4);

				if ( loop4 > 2 ) {
					return true;
				}
			}

			return false;
		}

		private bool TestCase5() const
		{
			print("TestCase 5: continue");

			for ( int loop5 = 0; loop5 < 10; loop5 = loop5 + 1 ) {
				if ( loop5 == 2 ) {
					continue;
				}

				if ( loop5 == 4 ) {
					return true;
				}
			}

			return false;
		}

		private bool TestCase6() const
		{
			print("TestCase 6: for ( ; ; )");

			int i = 0;
			for ( ; ; ) {
				print("" + i + ": for loop without condition");

				if ( i == 3 ) {
					break;
				}

				i++;
			}

			return true;
		}
	}
