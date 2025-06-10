#!/usr/local/bin/slang


public void Main( int argc, string args )
{
	double d = 1.2345678901234567890d;
	print( "d = " + d );

	double d2 = 1.23400000d;
	print( "d2 = " + d2 );

	double d3 = 1234.0000d;
	print( "d3 = " + d3 );

	double d4 = 0.000d;
	print( "d4 = " + d4 );

	float f = 1.234567890f;
	print( "f = " + f );

	float f2 = 1.230000000f;
	print( "f2 = " + f2 );
}

