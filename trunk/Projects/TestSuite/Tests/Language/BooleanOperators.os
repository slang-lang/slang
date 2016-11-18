#!/usr/local/bin/oscript

public void Main(int argc = 0, string argv = "") {
	assert( false == false );
	assert( true && true );
	assert( true || true );
	assert( true || false );
	assert( false !& false );
	assert( false !| false );
	assert( (1 == 1) && (2 == 2) );
	assert( (true == false) || (false == true) || (false) || (true) );

	bool bla = (false == false);
	assert(bla);
}

