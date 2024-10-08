
// declare 'System' namespace to prevent a user defined private 'System' namespace
public namespace System { }

public void debug( bool condition, string successMsg, string failMsg ) {
	if ( condition ) {
		print( successMsg );
		return;
	}

	print( failMsg );
}

public void error( bool condition, string successMsg, string failMsg ) {
	if ( condition ) {
		print( successMsg );
		return;
	}

	print( failMsg );
}

public void warn( bool condition, string successMsg, string failMsg ) {
	if ( condition ) {
		print( successMsg );
		return;
	}

	print( failMsg );
}

