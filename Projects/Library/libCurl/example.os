#!/usr/local/bin/slang

import Curl;

public void Main( int argc, string args ) modify {
	var curl = new CurlRequest( "https://api.exchange.bitpanda.com/public/v1/currencies" );

/*
	var settings = curl.settings();
	settings.ShowProgress = false;
	settings.VerboseOutput = false;
*/

	print( curl.execute() );
}

