#!/usr/local/bin/oscript

import System.String;

public void Main(int argc, string args) {
	print("Typecast expression");

	print( "cast<string>( 173 ): " + cast<string>( 173 ) );
	print( "cast<string>( \"173\".Length() ): " + cast<string>( "173".Length() ) );
	print( "cast<string>( new String( \"173\" ) ): " + cast<string>( new String("173") ) );

}

