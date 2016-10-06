#!/usr/local/bin/oscript

private object Main {
	public void Main(int argc = 0, string argv = "") {
		assert( false == false );
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

