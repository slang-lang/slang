#!/usr/local/bin/slang

public void Main( int, string )
{
	assert( TestCase1() );
}

private bool TestCase1()
{
	print( "TestCase 1: int32" );

	int i = 127;
	print( "i = " + i );

	return i == 127;
}

