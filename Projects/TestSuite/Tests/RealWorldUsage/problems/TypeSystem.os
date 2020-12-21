#!/usr/local/bin/slang

public void Main( int argc, string args ) {
	bool bval = 1;
	print( typeid( bval ) + ": " + bval );

	int ival = true;
	print( typeid( ival ) + ": " + ival );

	double dval = cast<double>( "17" );
	print( typeid( dval ) + ": " + dval );
}

