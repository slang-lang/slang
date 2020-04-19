#!/usr/local/bin/slang

import System.Collections.List;
import System.String;

int int(string value) {
	return int value;
}

string string(String value) {
	return string value;
}

public void Main(int argc, string args) {
	print("Typecast expression");

	print( "cast<string>( 173 ): " + cast<string>( 173 ) );
	print( "cast<string>( \"173\".Length() ): " + cast<string>( "173".Length() ) );
	print( "cast<string>( new String( \"173\" ) ): " + cast<string>( new String( "173" ) ) );
	print( "cast<string>( new String( 173 ) ): " + cast<string>( new String( 173 ) ) );
	print( cast<string>( "173.1389f" ) );

	print( cast<int>( cast<string>( new String( 1731389 ) ) ) );

	var list = new List<string>();
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");

	var it = list.getIterator();
	print( typeid( it ) );
	while ( it.hasNext() ) {
		it.next();

		print( cast<Iterator<string>>( it ).current() );
	}

	print( cast<int>( cast<string>( new String( 173 ) ) ) );
	//print( int new String( 173 ) );
}

