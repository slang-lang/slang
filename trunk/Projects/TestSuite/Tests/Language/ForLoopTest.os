#!/usr/local/bin/oscript

public namespace 
{
	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			for ( number loop1 = 0; loop1 < 5; loop1 = loop1 + 1; ) {
				print("loop1 = " + loop1);
				assert( loop1 < 5 );
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert( loop1 == 5 );

			for ( number loop2 = 0; loop2 < 10; loop2 = loop2 + 1; ) {
				print("loop2 = " + loop2);
				assert( loop2 < 10 );
			}
			// if this assert fails or succeeds, either way this means our scopes are not working correctly
			// we should never ever be able to access a variable that was declared in a loop
			assert( loop2 == 10 );

			for ( number loop3 = 0; loop3 < 5; loop3 = loop3 + 1; ) {
				print("loop3 = " + loop3);
				assert( loop3 < 5 );

				if ( loop3 > 2 ) {
					break;
				}
			}
			assert( loop3 == 3 );
		}
	}
}
