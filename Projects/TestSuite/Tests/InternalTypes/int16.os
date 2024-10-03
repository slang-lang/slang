#!/usr/local/bin/slang

public void Main( int, string )
{
	assert( TestCase1() );
}

private bool TestCase1()
{
	print( "TestCase 1: int16" );

	int16 i = 127;
	print( "i = " + i );

	return true;
}

