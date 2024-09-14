#!/usr/local/bin/slang

import CurlRequest;

public void Main( int argc, string args ) modify {
	var curl = new CurlRequest( "https://api.exchange.bitpanda.com/public/v1/time" );

	//curl.setData( "" );
	//curl.setHeader( "" );

/*
	var settings = curl.settings();
	settings.ShowProgress = false;
	settings.VerboseOutput = false;
*/

	print( curl.execute() );
}

