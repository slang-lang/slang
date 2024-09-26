#!/usr/local/bin/slang

import System.Exception;
import System.String;

public void Main( int argc, string args ) throws
{
	//throw new ArithmeticException( "exception" );
	throw new String( "This is a String exception" );
}

