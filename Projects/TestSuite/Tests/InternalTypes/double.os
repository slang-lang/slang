#!/usr/local/bin/slang

public void Main( int argc, string args )
{
	var i = 17.d;
	print( typeid( i ) + " = " + i );

	assert( i == 17d );
}

