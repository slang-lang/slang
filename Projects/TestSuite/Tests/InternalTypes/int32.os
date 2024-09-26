#!/usr/local/bin/slang

public void Main( int, string )
{
	assert( TestCase1() );
	assert( TestCase2() );
}

private bool TestCase1()
{
	print( "TestCase 1: int32" );

	int i = 127;
	print( "i = " + i );

	return i == 127;
}

private bool TestCase2()
{
	print( "TestCase 2: 17i" );

	var i = 17i;
	print( typeid( i ) + " = " + i );

	return i == 17;
}

