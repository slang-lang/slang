#!/usr/local/bin/oscript

public namespace BooleanOperators
{
	private object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			assert true;
			assert false == false;
			assert( true && true );
			assert( false || true );
			assert( false !& false );
			assert( false !| false );
			assert( (1 == 1) && (2 == 2) );
			assert( (true == false) || (false == true) || (false) || (true) );
			//assert( true > false );	// operator> for boolean type not implemented, this is perfectly okay

			bool bla = (false == false);
			assert(bla);
		}
	}
}
