#!/usr/local/bin/slang

public void Main( int argc, string args )
{
	var i = 17.f;
	print( typeid( i ) + " = " + i );

	assert( i == 17f );
}

