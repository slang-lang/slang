#!/usr/local/bin/oscript

import system.assert;

public namespace BooleanOperators
{
	private object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert( true && true );
			assert( true || false );
			//assert( 1 == 0 );
		}
	}
}
