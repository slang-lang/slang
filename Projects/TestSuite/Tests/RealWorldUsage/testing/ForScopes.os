#!/usr/bin/env slang

import System.Collections.Range;

public void Main(int argc, string args) {
	for ( int i = 0; i < 5; i++ );
		//print(i);

	for ( int i = 0; i < 10; i++ );
		//print(i);

	foreach ( int fe : 1..5 );
		//print(fe);

	foreach ( int fe : 1..10 );
		//print(fe);
}

